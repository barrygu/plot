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

clean:
	rm -f *.o simple simple_curses
