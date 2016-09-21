CC     = gcc
CFLAGS = -Wall -W -std=c99 -pedantic -Iinc -g3

EXECS = main

.c.o :
	$(CC) -c $(CFLAGS) $*.c

all :: $(EXECS)

$(EXECS) : %: %.o
	$(CC) -o $@ $@.o

clean ::
	\rm -f *.o $(EXECS)
