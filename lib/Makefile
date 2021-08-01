include $(TOPDIR)/makefile.inc
ver := 0.5.0
rev := ${shell git rev-parse --short HEAD}

all: libplot.a

SRCS = data_pipe.c \
	data_proc.c \
	display.c \
	file_input.c \
	log.c \
	plot.c \
	util.c \
	version.c

OUTDIR := objs
OBJS = $(patsubst %.c, $(OUTDIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -I../include -c $< -o $@

libplot.a: $(OBJS)
	$(AR) -crv $@ $^
	$(RANLIB) $@

$(OBJS) $(DEPS): | $(OUTDIR)
$(OUTDIR):
	mkdir $(OUTDIR)

-include $(DEPS)

$(OUTDIR)/%.d: %.c
	$(CC) -MM -MG $< $(CFLAGS) -I../include | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@' > $@

depend: $(DEPS)

version.c: version.c.in
	sed "s/@version@/$(ver)/;s/@vcs_tag@/$(rev)/" $< > $@

clean:
	rm -rf $(OUTDIR) *.a version.c
