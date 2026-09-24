# Bornomala SDK

PREFIX ?= /opt/BornomalaSDK

CROSS ?= $(shell command -v x86_64-linux-gnu-gcc >/dev/null 2>&1 && echo x86_64-linux-gnu- || echo)

CC=$(CROSS)gcc

CFLAGS=-std=gnu99 -D_XOPEN_SOURCE=700 -Wall -Wextra -O2

SRC=src/main.c \
    src/commands.c \
    src/project.c \
    src/build.c \
    src/pack.c \
    src/doctor.c

TARGET=bin/bsa

.PHONY: all install clean uninstall

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	sudo mkdir -p /usr/local/bin
	sudo mkdir -p $(PREFIX)
	sudo cp $(TARGET) /usr/local/bin/bsa
	sudo cp -r sdk $(PREFIX)/
	sudo cp -r templates $(PREFIX)/
	@if [ -d docs ]; then sudo cp -r docs $(PREFIX)/; fi
	@echo "Installed."

uninstall:
	sudo rm -f /usr/local/bin/bsa
	sudo rm -rf $(PREFIX)

clean:
	rm -rf bin