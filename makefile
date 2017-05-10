CC=gcc
CFLAGS=-Wall -g -std=c99
LDFLAGS=-g

all: now when libmessage.so periodic launch_daemon period

now: now.o
	$(CC) $(LDFLAGS) -o $@ $<

now.o: now.c
	$(CC) -c $(CFLAGS) -o $@ $<

when: when.o
	$(CC) $(LDFLAGS) -o $@ $<

when.o: when.c
	$(CC) -c $(CFLAGS) -o $@ $<

libmessage.so: message.o
	$(CC) $(LDFLAGS) -o $@ -shared $<

message.o: message.c message.h
	$(CC) -c $(CFLAGS) -o $@ $< -fPIC

periodic: periodic.o
	$(CC) $(LDFLAGS) -o $@ $< -lmessage -L./

periodic.o: periodic.c
	$(CC) -c $(CFLAGS) -o $@ $< 

period: period.o
	$(CC) $(LDFLAGS) -o $@ $< -lmessage -L./

period.o: period.c
	$(CC) -c $(CFLAGS) -o $@ $< 

launch_daemon: launch_daemon.o
	$(CC) $(LDFLAGS) -o $@ $<

launch_daemon.o: launch_daemon.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean: 
	rm -f *.o
mrproper: clean
	rm -f now when libmessage.so periodic launch_daemon period
