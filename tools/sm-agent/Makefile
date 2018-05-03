CC = gcc
CFLAGS += -Wall
PREFIX ?= /usr/local
BIN = sm-agent

all: clean $(BIN)

$(BIN):
	$(CC) $(CFLAGS) *.c -o $(BIN)

install: o4l
	install -d $(PREFIX)/bin
	install -m755 lm $(PREFIX)/bin/$(BIN)

clean:
	rm -f $(BIN)
