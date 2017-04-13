CC=gcc
CFLAGS=-Wall -g -std=c99
LDFLAGS=-g

all: now when

now: now.o
	$(CC) $(LDFLAGS) -o $@ $<

now.o: now.c
	$(CC) -c $(CFLAGS) -o $@ $<

when: when.o
	$(CC) $(LDFLAGS) -o $@ $<

when.o: when.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean: 
	rm -f *.o
mrproper: clean
	rm -f now when
