//  http://hertaville.com/2012/11/18/introduction-to-accessing-the-raspberry-pis-gpio-in-c/

#if DEBUG
#include <iostream>
#endif
#include <fstream>
//#include <stdio.h>	/* printf, fgets */
#include <stdlib.h>	/* atoi */
#include <stdint.h>
#include <time.h>	/* strftime */
//#include <libconfig.h++>  /*  */

#define DATAPIN		18
#define CLOCKPIN	24
#define LACHPIN		23

#define LSBFIRST	0
#define MSBFIRST	1
#define LOW		0
#define HIGH		1

// Display output pin assignments
#define THREE   Display[0] |= (1<<0)
#define SIX     Display[0] |= (1<<1)
#define TWELVE  Display[0] |= (1<<2)
#define NINE    Display[0] |= (1<<3)
#define MFIVE   Display[0] |= (1<<4)
#define OCLOCK  Display[0] |= (1<<5)
#define TWENTY  Display[0] |= (1<<6)
#define TWO     Display[1] |= (1<<0)
#define HFIVE   Display[1] |= (1<<1)
#define TO      Display[1] |= (1<<2)
#define EIGHT   Display[1] |= (1<<3)
#define MTEN    Display[1] |= (1<<4)
#define ELEVEN  Display[1] |= (1<<5)
#define HALF    Display[1] |= (1<<6)
#define ONE     Display[2] |= (1<<0)
#define FOUR    Display[2] |= (1<<1)
#define PAST    Display[2] |= (1<<2)
#define SEVEN   Display[2] |= (1<<3)
#define QUARTER Display[2] |= (1<<4)
#define HTEN    Display[2] |= (1<<5)
#define ITIS    Display[2] |= (1<<6)

#define APMODE  Display[0] |= (1<<7)
#define TIME    Display[1] |= (1<<7)
#define CONFIG  Display[2] |= (1<<7)

using namespace std;

const int currentHour() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[10];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%I", &tstruct);

	return atoi(buf);
}

const int currentMinute() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[10];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%M", &tstruct);

	return atoi(buf);
}

void digitalWrite(int pin, int value) {
	fstream gpioWrite;
	string sWrite = "/sys/class/gpio/gpio" + to_string(pin) + "/value";
	gpioWrite.open(sWrite.c_str(), fstream::out);
	gpioWrite << to_string(value);
	gpioWrite.close();
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val){
	int i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else
			digitalWrite(dataPin, !!(val & (1 << (7 - i))));

		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);  
	}

}

int main() {

    #ifdef DEBUG
    cout << "currentTime=" << currentHour() << ":" << currentMinute() << endl;
    #endif

    string sPath = "/sys/class/gpio/gpio";
    string sFilename;

    fstream gpio;
    gpio.open("/sys/class/gpio/export", fstream::out);
    gpio << LACHPIN;
    gpio.close();

    gpio.open("/sys/class/gpio/export", fstream::out);
    gpio << DATAPIN;
    gpio.close();

    gpio.open("/sys/class/gpio/export", fstream::out);
    gpio << CLOCKPIN;
    gpio.close();

    sFilename = sPath + to_string(LACHPIN) + "/direction";
    gpio.open(sFilename.c_str(), fstream::out);
    gpio << "out";
    gpio.close();

    sFilename = sPath + to_string(DATAPIN) + "/direction";
    gpio.open(sFilename.c_str(), fstream::out);
    gpio << "out";
    gpio.close();

    sFilename = sPath + to_string(CLOCKPIN) + "/direction";
    gpio.open(sFilename.c_str(), fstream::out);
    gpio << "out";
    gpio.close();

    int iHour=currentHour();
    int iMinute=currentMinute();

    char Display[3]={0,0,0};

    ITIS;
    #ifdef DEBUG
    cout << "It is ";
    #endif

    switch (iMinute) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            OCLOCK;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            MFIVE;
            PAST;
            #ifdef DEBUG
            cout << "Five Past ";
            #endif
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            MTEN;
            PAST;
            #ifdef DEBUG
            cout << "Ten Past ";
            #endif
            break;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            QUARTER;
            PAST;
            #ifdef DEBUG
            cout << "Quarter Past ";
            #endif
            break;
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            TWENTY;
            PAST;
            #ifdef DEBUG
            cout << "Twenty Past ";
            #endif
            break;
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
            TWENTY;
            MFIVE;
            PAST;
            #ifdef DEBUG
            cout << "Twenty Five Past ";
            #endif
            break;
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
            HALF;
            PAST;
            #ifdef DEBUG
            cout << "Half Past ";
            #endif
            break;
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
            TWENTY;
            MFIVE;
            TO;
            iHour=iHour+1;
            #ifdef DEBUG
            cout << "Twenty Five To ";
            #endif
            break;
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
            TWENTY;
            TO;
            iHour=iHour+1;
            #ifdef DEBUG
            cout << "Twenty To ";
            #endif
            break;
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            QUARTER;
            TO;
            iHour=iHour+1;
            #ifdef DEBUG
            cout << "Quarter To ";
            #endif
            break;
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            MTEN;
            TO;
            iHour=iHour+1;
            #ifdef DEBUG
            cout << "Ten To ";
            #endif
            break;
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
            MFIVE;
            TO;
            iHour=iHour+1;
            #ifdef DEBUG
            cout << "Five To ";
            #endif
            break;
        default:
            break;
    }

    switch (iHour) {
        case 1:
        case 13:
            ONE;
            #ifdef DEBUG
            cout << "One";
            #endif
            break;
        case 2:
            TWO;
            #ifdef DEBUG
            cout << "Two";
            #endif
            break;
        case 3:
            THREE;      
            #ifdef DEBUG
            cout << "Three";
            #endif
            break;
        case 4:
            FOUR;      
            #ifdef DEBUG
            cout << "Four";
            #endif
            break;
        case 5:
            HFIVE;      
            #ifdef DEBUG
            cout << "Five";
            #endif
            break;
        case 6:
            SIX;      
            #ifdef DEBUG
            cout << "Six";
            #endif
            break;
        case 7:
            SEVEN;      
            #ifdef DEBUG
            cout << "Seven";
            #endif
            break;
        case 8:
            EIGHT;      
            #ifdef DEBUG
            cout << "Eight";
            #endif
            break;
        case 9:
            NINE;      
            #ifdef DEBUG
            cout << "Nine";
            #endif
            break;
        case 10:
            HTEN;      
            #ifdef DEBUG
            cout << "Ten";
            #endif
            break;
        case 11:
            ELEVEN;      
            #ifdef DEBUG
            cout << "Eleven";
            #endif
            break;
        case 0:
        case 12:
            TWELVE;      
            #ifdef DEBUG
            cout << "Twelve";
            #endif
            break;
    }

    #ifdef DEBUG
    switch (iMinute) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            cout << " O'Clock";
            break;
    }

    cout << endl;
    #endif

    digitalWrite(LACHPIN, LOW);

    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, Display[2]);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, Display[1]);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, Display[0]);

    digitalWrite(LACHPIN, HIGH);

    gpio.open("/sys/class/gpio/unexport", fstream::out);
    gpio << LACHPIN;
    gpio.close();

    gpio.open("/sys/class/gpio/unexport", fstream::out);
    gpio << DATAPIN;
    gpio.close();

    gpio.open("/sys/class/gpio/unexport", fstream::out);
    gpio << CLOCKPIN;
    gpio.close();

    return 0;
}

