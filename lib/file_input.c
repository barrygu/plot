#include "posix.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "internal/data_proc.h"
#include "internal/log.h"
#include "internal/util.h"
#include "plot/file_input.h"
#include "plot/plot.h"

bool
plot_file_input_init(struct plot_file_input *in, char *buf, uint32_t buf_max,
	FILE *f, enum plot_file_input_flags flags)
{
	assert(buf_max);

	*in = (struct plot_file_input) {
		.buf = buf,
		.buf_max = buf_max,
		.flags = flags,
	};

	in->src = f;

	return true;
}


static bool
start_of_number(char c)
{
	switch (c) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '-': case '+':
		return true;
	default:
		return false;
	}
}

int
input_timeout (int filedes, unsigned int ms)
{
	int retvar;
	fd_set set;
	struct timeval timeout;

	/* Initialize the file descriptor set. */
	FD_ZERO (&set);
	FD_SET (filedes, &set);

	/* Initialize the timeout data structure. */
	timeout.tv_sec = 0;
	timeout.tv_usec = ms * 1000;

	/* select returns 0 if timeout, 1 if input available, -1 if error. */
	do {
		retvar = select (FD_SETSIZE, &set, NULL, NULL,&timeout); 
	} while (retvar == -1 && errno == EINTR);
	return retvar;
}

uint32_t
plot_file_input_read(struct plot_file_input *in, double *out, uint32_t out_max)
{
	char *endptr = NULL;
	size_t i = 0, buflen, oldi = 0;
	double tmp;
	uint32_t out_len = 0;

	if (feof(in->src)) {
		if (in->flags & plot_file_input_flag_infinite) {
			clearerr(in->src);
			if (in->flags & plot_file_input_flag_rewind) {
				rewind(in->src);
			}
		}

		return 0;
	}

	assert(in->rem <= (in->buf_max - 1));

	buflen = 0;
	do {
		int available = input_timeout(fileno(in->src), 50);
		if (available) {
			int ch = fgetc(in->src);
			in->buf[in->rem+buflen] = ch;
			buflen++;
			if ((in->flags & plot_file_input_flag_infinite) && !start_of_number(ch))
				break;
		}
		else if (in->flags & plot_file_input_flag_infinite)
			break;
	} while (buflen < (in->buf_max - 1) - in->rem);

	in->buf[in->rem+buflen] = 0;
	if (!buflen) {
		if (errno == EAGAIN || !errno) {
			return 0;
		} else {
			fprintf(stderr, "error reading from file %d: %s\n", errno, strerror(errno));
			return 0;
		}
	}

	buflen += in->rem;

	while (i < buflen) {
		if (!start_of_number(in->buf[i])) {
			++i;
			continue;
		}

		errno = 0;
		tmp = strtod(&in->buf[i], &endptr);
		if (endptr == &in->buf[i] || errno) {
			++i;
			continue;
		}

		oldi = i;

		i += endptr - &in->buf[i];

		out[out_len] = tmp;
		if (++out_len >= out_max) {
			break;
		}
	}

	if (i == buflen && !feof(in->src)) {
		// The last number we read ended right at the end of the
		// buffer, but there is still more to read.  unread this number
		// for now in case only a portion of it is in the buffer
		assert(out_len);
		--out_len;
		i = oldi;
	}

	if ((in->rem = buflen - i)) {
		memmove(in->buf, &in->buf[i], in->rem);
	}

	memset(&in->buf[in->rem], 0, (in->buf_max - 1) - in->rem);

	return out_len;
}
