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
	cp bin/* /usr/local/bin/
	chown root. /usr/local/bin/clock-time
	chown root. /usr/local/bin/clock-color
	chmod u+s /usr/local/bin/clock-time
	chmod u+s /usr/local/bin/clock-color

uninstall:
	rm /usr/local/bin/clock-time
	rm /usr/local/bin/clock-color
	rm /usr/local/bin/clock-config
