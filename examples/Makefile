include ../makefile.inc

BINS := simple simple_curses
all: $(BINS)

CFLAGS += -I../include
LINK_FLAGS += -L../lib -lplot

LIBS := ../lib/libplot.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

simple: simple.o $(LIBS)
	$(CC) -o $@ $(filter-out %.a, $^) $(LINK_FLAGS)

LIBNCURSES:=-lncurses
#LIBNCURSES+=-ltinfo
simple_curses: simple_curses.o $(LIBS)
	$(CC) -o $@ $(firstword $^) $(LINK_FLAGS) $(LIBNCURSES)

ifneq ($(MAKECMDGOALS),clean)
-include simple.d simple_curses.d
endif

%.d: %.c
	$(CC) -MM -MG $< $(CFLAGS) -I../include | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@' > $@

depend: $(DEPS)

clean:
	rm -f *.o *.d simple simple_curses
