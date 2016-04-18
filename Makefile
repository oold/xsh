CC = /usr/bin/gcc
CFLAGS = -Wall -Wpedantic
NAME = xsh
CFILES = main.c read.c signals.c log.c util.c

default:
	mkdir -p release
	$(CC) $(CFLAGS) -O2 -o release/$(NAME) $(CFILES)

debug:
	mkdir -p debug
	$(CC) $(CFLAGS) -g -o debug/$(NAME) $(CFILES)

clean:
	rm -rf release/ debug/
