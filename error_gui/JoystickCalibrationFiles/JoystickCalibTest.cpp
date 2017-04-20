
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "JoystickCalib.h"

int main()
{
	JoystickCalib jCalib;

	std::cout << "Starting MAX calibration test" << std::endl;
	jCalib.startCalicration(CALIB_MAX);
	std::srand(std::time(0));
	for(int i=0; i<20; i++)
	{
		ushort randSample = (ushort)(std::rand());
		randSample = randSample % 36;
		randSample = randSample + 4060;
		jCalib.pushSample(randSample);
		std::cout << randSample << std::endl;
	}
	std::cout << "Calibrated MAX Value:" <<jCalib.getCalibratedValue()
	          << std::endl;

	std::cout << std::endl << "Starting MIN calibration test" << std::endl;
	jCalib.startCalicration(CALIB_MIN);
	std::srand(std::time(0));
	for(int i=0; i<20; i++)
	{
		ushort randSample = (ushort)(std::rand());
		randSample = randSample % 36;
		randSample = randSample;
		jCalib.pushSample(randSample);
		std::cout << randSample << std::endl;
	}
	std::cout << "Calibrated MIN Value:" <<jCalib.getCalibratedValue()
	          << std::endl;


	std::string testFileName("CalibTestFile");
	ushort calibVals[] = {11,22,33,44};

	JoystickCalib::writeToFile(calibVals, testFileName.c_str());

	ushort calibValsRead[4];
	JoystickCalib::readFromFile(calibValsRead, testFileName.c_str());
	std::cout << calibValsRead[0] << std::endl
			  << calibValsRead[1] << std::endl
			  << calibValsRead[2] << std::endl
			  << calibValsRead[3] << std::endl;
}