CC=gcc
CFLAGS=-Wall -g -std=c99
LDFLAGS=-g

all: now when message period

now: now.o
	$(CC) $(LDFLAGS) -o $@ $<

now.o: now.c
	$(CC) -c $(CFLAGS) -o $@ $<

when: when.o
	$(CC) $(LDFLAGS) -o $@ $<

when.o: when.c
	$(CC) -c $(CFLAGS) -o $@ $<

message: message.o
	$(CC) $(LDFLAGS) -o $@ $<

message.o: message.c
	$(CC) -c $(CFLAGS) -o $@ $<

period: period.o
	$(CC) $(LDFLAGS) -o $@ $<

period.o: period.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean: 
	rm -f *.o
mrproper: clean
	rm -f now when message period
