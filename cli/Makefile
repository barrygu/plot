include $(TOPDIR)/makefile.inc

all: plot

SRCS = animate.c \
	main.c \
	opts.c

OBJS = $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

%.o: %.c
	$(CC) $(CFLAGS) -I$(TOPDIR)/include -c $< -o $@

plot: $(OBJS) $(TOPDIR)/lib/libplot.a
	$(CC) -o $@ $(OBJS) -lplot $(LINK_FLAGS) -L$(TOPDIR)/lib
#	$(CC) $(LINK_FLAGS) -o $@ $^ ../lib/libplot.a

-include $(DEPS)

%.d: %.c
	$(CC) -MM -MG $< $(CFLAGS) -I../include | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@' > $@

depend: $(DEPS)

clean:
	rm -f *.o *.d plot
