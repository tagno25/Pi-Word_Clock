DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS = -lconfig++ -std=c++0x -DDEBUG
else
	CFLAGS = -lconfig++ -std=c++0x
endif

all: time color config

time:
	g++ -o clock-time clock-time.cpp -lwiringPi $(CFLAGS)

color:
	g++ -o clock-color clock-color.cpp $(CFLAGS)

config:
	g++ -o clock-config clock-config.cpp $(CFLAGS)

.PHONY: time color clean config

clean:
	rm clock-time clock-color clock-config

install:
	cp clock-time /usr/local/bin/
	chown root. /usr/local/bin/clock-time
	chmod u+s /usr/local/bin/clock-time
	cp clock-color /usr/local/bin/
	chown root. /usr/local/bin/clock-color
	chmod u+s /usr/local/bin/clock-color
	cp clock-config /usr/local/bin/

uninstall:
	rm /usr/local/bin/clock-time
	rm /usr/local/bin/clock-color
	rm /usr/local/bin/clock-config
