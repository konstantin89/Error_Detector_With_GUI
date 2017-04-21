/**********************************************************************
*
* @author: Kosta Bulgakov
*
* @date: 20-04-2017
*
* @brief: Source file for joystick callibration class.
*
**********************************************************************/


#include "JoystickCalib.h"

JoystickCalib::JoystickCalib()
{
	/* EMPTY */
}

JoystickCalib::~JoystickCalib()
{
	/* EMPTY */
}

void JoystickCalib::refreshSamples()
{
	_sampleVec.clear();
}

void JoystickCalib::startCalicration(char calibType)
{
	refreshSamples();
	_calibFlag = calibType;
}

void JoystickCalib::pushSample(ushort sample)
{
	_sampleVec.push_back(sample);
}

ushort JoystickCalib::getCalibratedValue()
{
	if(_calibFlag == CALIB_MIN)
	{
		std::sort(_sampleVec.begin(), _sampleVec.end());
	}
	else
	{
		std::reverse(_sampleVec.begin(), _sampleVec.end());
	}
	int vecSize = _sampleVec.size();

	uint sum = 0;
	int samplesToSum = (int)(vecSize/10);
	for(int i=0; i<samplesToSum; i++)
		sum += _sampleVec[i];

	return (ushort)(sum/samplesToSum);

}

int JoystickCalib::writeToFile(ushort* vals, const char* fname)
{
	 std::ofstream fStream;
	 fStream.open(fname, std::ios::out);
	 if(!fStream.is_open())
	 {
	 	return MY_ERROR;
	 }
	 fStream << vals[0] << std::endl 
	 		 << vals[1] << std::endl
	 		 << vals[2] << std::endl
	 		 << vals[3] << std::endl;

	 fStream.close();
	 return SUCCESS;
}


int JoystickCalib::readFromFile(ushort* retVals, const char* fname)
{
	std::string line;
	std::ifstream fStream(fname);
	if(!fStream.is_open())
	{
	 	return MY_ERROR;
	}

	for(int i=0; i<4 ;i++)
	{
		getline (fStream,line);
		int value = std::stoi(line);
		retVals[i] = (ushort)value;
	}
	return SUCCESS;
}


/************************* End Of File ******************************/
