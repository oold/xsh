CC = /usr/bin/gcc
CFLAGS = -Wall
NAME = xsh
CFILES = main.c read.c signals.c log.c util.c
OLEVEL = 3

default:
	mkdir -p release
	$(CC) $(CFLAGS) -O$(OLEVEL) -o release/$(NAME) $(CFILES)

debug:
	mkdir -p debug
	$(CC) $(CFLAGS) -g -o debug/$(NAME) $(CFILES)

clean:
	rm -rf release/ debug/
