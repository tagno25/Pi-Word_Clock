#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <string>

#include <libconfig.h++>

#include <yaml-cpp/yaml.h>

using namespace std;
using namespace libconfig;

//------------------libcurl------------------
//
//  http://stackoverflow.com/questions/1129194/download-a-url-in-c
//  http://curl.haxx.se/libcurl/

//-------------------Config------------------
//
//  http://www.hyperrealm.com/libconfig/
//
//  /usr/share/doc/libconfig++-dev/examples/example1.cpp.gz
//

// clock-config -w selected.option value //write config
// clock-config -r selected.option //read config
// clock-config -c selected.option //read color
// clock-config -u //update color config

int complain( const string& progname ) {
	cerr << "Hey, program arguments must be \"-n\" followed by a non-zero, positive integer, as in:" << endl << endl
		<< " " << progname << " -n 150" << endl << endl
		<< "The default is 100." << endl;
	return 1;
}


int configWrite(const char* file, string option, string value) {
	
	return 0;
}

int configRead(const char* file, string option, int loop) {

	Config cfg;

	try
	{
		cfg.readFile(file);
	}
	catch(const FileIOException &fioex)
	{
		cerr << "I/O error while reading file." << std::endl;
		return EXIT_FAILURE;
	}
	catch(const ParseException &pex)
	{
		cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
			<< " - " << pex.getError() << endl;
		return EXIT_FAILURE;
	}

	if (cfg.getRoot()[option].isGroup() || cfg.getRoot()[option].isArray() || cfg.getRoot()[option].isList()){
//		for (int i=0;i<cfg.getRoot()[option].getLength();i++){
//			 cerr << cfg.getRoot()[option][i].getName() << endl;
//		}
		return 0;
	}
	
	try {
		//cfg.getRoot()[option].getType()
		if(loop=0){
			cout << (const char *)cfg.lookup(option) << endl;
		} else if(loop=1) {
			cout << (int)cfg.lookup(option) << endl;
		} else {
			return 0;
		}
	} catch(const SettingNotFoundException &nfex) {
		cerr << "Setting Not Found" << endl;
		return EXIT_FAILURE;
	} catch(const SettingTypeException &nfex) {
		cerr << "Setting Type" << loop << endl;
		int j = loop+1;
		cerr << j << endl;
		configRead(file,option,j);
		return EXIT_FAILURE;
	}
}

int configUpdate() {

	//wget configRead("/opt/clock/clock.cfg", "remote.host") -c /opt/clock/color.cfg

}

int main(int argc, char* argv[])
{
	string sValue;

	if (argc == 1){
		return complain(argv[0]);
	} else if (argc == 3 && string(argv[1]) == "-r") {
		return configRead("/opt/clock/clock.cfg", argv[2], 0);//read main config
	} else if (argc == 3 && string(argv[1]) == "-c") {
                return configRead("/opt/clock/color.cfg", argv[2], 0);//read color config
        } else if (argc == 4 && string(argv[1]) == "-w") {
		return configWrite("/opt/clock/clock.cfg", argv[2], argv[3]);//write main config
	} else if (string(argv[1]) == "-u") {
		return configUpdate();
	} else {
		return complain(argv[0]);
	}
}
