DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS = -lconfig++ -std=c++0x -DDEBUG
else
	CFLAGS = -lconfig++ -std=c++0x
endif
BINDIR := bin

all: time color config

$(BINDIR):
	mkdir -p $(BINDIR)


time: | $(BINDIR)
	g++ -o bin/clock-time clock-time.cpp -lwiringPi $(CFLAGS)

color: | $(BINDIR)
	g++ -o bin/clock-color clock-color.cpp $(CFLAGS)

config: | $(BINDIR)
	g++ -o bin/clock-config clock-config.cpp $(CFLAGS)

.PHONY: time color clean config

clean:
	rm bin/*

install:
	chown root. bin/clock-time
	chown root. bin/clock-color
	chmod u+s bin/clock-time
	chmod u+s bin/clock-color
	cp bin/* /usr/local/bin/

uninstall:
	rm /usr/local/bin/clock-time
	rm /usr/local/bin/clock-color
	rm /usr/local/bin/clock-config
