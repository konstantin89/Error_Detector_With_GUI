/**********************************************************************
*
* @author: Kosta Bulgakov
*
* @date: 20-04-2017
*
* @brief: Header file for joystick callibration class.
*
**********************************************************************/

#ifndef _JOYSICK_CALIBR_H
#define _JOYSICK_CALIBR_H

#include <vector>
#include <algorithm> 
#include <fstream>

#define CALIB_MIN 0
#define CALIB_MAX 1
#define NOT_DEFINED -1

#ifndef MY_ERROR
#define MY_ERROR -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

class JoystickCalib
{
private:
	std::vector<ushort> _sampleVec;
	char _calibFlag = CALIB_MAX;
public:
	JoystickCalib();
	~JoystickCalib();
	void refreshSamples();
	void startCalicration(char calibType);
	void pushSample(ushort sample);
	ushort getCalibratedValue();

	static int writeToFile(ushort* vals, const char* fname);
	static int readFromFile(ushort* retVals, const char* fname);
};

#endif

/************************* End Of File ******************************/

