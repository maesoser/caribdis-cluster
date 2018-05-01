CC = gcc
CFLAGS += -Wall
PREFIX ?= /usr/local

all: sm-client

sm-client:
	$(CC) $(CFLAGS) *.c -o sm-client

install: o4l
	install -d $(PREFIX)/bin
	install -m755 lm $(PREFIX)/bin/sm-client

clean:
	rm -f lm
