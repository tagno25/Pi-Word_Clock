#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <libconfig.h++>
#include <string>

using namespace std;
using namespace libconfig;

//  http://www.cplusplus.com/articles/DEN36Up4/
//  http://www.cprogramming.com/tutorial/lesson14.html
//  http://www.cplusplus.com/reference/cstdlib/getenv/

//--------------------LED--------------------
//
//  http://derekmolloy.ie/beaglebone-controlling-the-on-board-leds-using-c/
//
//  kernel module leds-pca963x
//  https://stuff.mit.edu/afs/sipb/contrib/linux/drivers/leds/leds-pca963x.c
//
//  http://www.crashcourse.ca/wiki/index.php/LEDs_on_the_BBB
//  https://www.kernel.org/doc/Documentation/leds/leds-class.txt
//  https://www.kernel.org/doc/Documentation/leds/leds-blinkm.txt
//  https://www.kernel.org/doc/Documentation/devicetree/bindings/leds/pca963x.txt

//-------------------Config------------------
//
//  http://www.hyperrealm.com/libconfig/
//

#define LED_RED "1"
#define LED_GREEN "2"
#define LED_BLUE "0"

int main(int argc, char* argv[])
{	
	Config cfg;

	try
	{
		cfg.readFile("/opt/clock/clock.cfg");
	}
	catch(const FileIOException &fioex)
	{
		std::cerr << "I/O error while reading file." << std::endl;
		return(EXIT_FAILURE);
	}
	catch(const ParseException &pex)
	{
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
			<< " - " << pex.getError() << std::endl;
	return(EXIT_FAILURE);
	}

	string sLedPathRed = "/sys/class/leds/pca963x:1:60:";
	int iLedRed, iLedGreen, iLedBlue;
	try {
		iLedRed = cfg.lookup("RedOutput");
	} catch(const SettingNotFoundException &nfex) {
		iLedRed = 1;
	}

	try {
		iLedGreen = cfg.lookup("GreenOutput");
	} catch(const SettingNotFoundException &nfex) {
		iLedGreen = 2;
	}

	try {
		iLedBlue = cfg.lookup("BlueOutput");
	} catch(const SettingNotFoundException &nfex) {
		iLedBlue = 0;
	}

	// Check the number of parameters
	if (argc < 4) {
		// Tell the user how to run the program
		cerr << "Usage: " << argv[0] << " Red Green Blue" << endl;
		/* "Usage messages" are a conventional way of telling the user
		 * how to run a program if they enter the command incorrectly.
		 */
		return 1;
	}

	int iColor[3]={0,0,0};

	for (int n=0; n<3; n++){
	iColor[n]=atoi(argv[n+1]);

		if (iColor[n]>=255){
			iColor[n]=255;
		}

	}

	#ifdef DEBUG
	cout << "Red = " << iColor[0] << endl;
	cout << "Green = " << iColor[1] << endl;
	cout << "Blue = " << iColor[2] << endl;
	#endif

	fstream fs;
	
	string sPath = "/sys/class/leds/pca963x:1:60:";
	string sFile = "/brightness";
	string sFilename;

	sFilename = sPath + to_string(iLedRed) + sFile;
	fs.open (sFilename.c_str(), fstream::out);
	fs << iColor[0];
	fs.close();

	sFilename = sPath + to_string(iLedGreen) + sFile;
	fs.open (sFilename.c_str(), fstream::out);
	fs << iColor[1];
	fs.close();

	sFilename = sPath + to_string(iLedBlue) + sFile;
	fs.open (sFilename.c_str(), fstream::out);
	fs << iColor[2];
	fs.close();

	return 0;
}
