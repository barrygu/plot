include $(TOPDIR)/makefile.inc

all: plot

SRCS = animate.c \
	main.c \
	opts.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I$(TOPDIR)/include -c $< -o $@

plot: $(OBJS) $(TOPDIR)/lib/libplot.a
	$(CC) -o $@ $(OBJS) -lplot $(LINK_FLAGS) -L$(TOPDIR)/lib
#	$(CC) $(LINK_FLAGS) -o $@ $^ ../lib/libplot.a

clean:
	rm -f *.o plot
