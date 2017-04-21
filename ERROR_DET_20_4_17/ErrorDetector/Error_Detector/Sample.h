/**********************************************************
*
* @author: Kosta Bulgakov
*
* @date: 28/12/2016
*
* @brief: File contains definition of class that
*         represents sample from AD7992 device.
*
*
***********************************************************/

#include <chrono>
#include "../AD9772_Comm_Module/AD9772_Comm.h"
#ifndef SAMPLE_H
#define SAMPLE_H


class Sample
{
private:
	WCHAR _convertedValueX;
	WCHAR _convertedValueY;
	std::chrono::steady_clock::time_point _sampleTime;

public:	
	Sample(){};
	Sample(WCHAR valueChX, WCHAR valueChY, std::chrono::steady_clock::time_point sampleTime)
	{
		_convertedValueX = valueChX;
		_convertedValueY = valueChY;
		_sampleTime = sampleTime;
	}

	~Sample()
	{
		/* EMPTY */
	}

	WCHAR getValueX()
	{
		return _convertedValueX;
	}

	WCHAR getValueY()
	{
		return _convertedValueY;
	}
	std::chrono::steady_clock::time_point getTime()
	{
		return _sampleTime;
	}
};


typedef Sample* PSample;
#endif

/******************** End of file **********************/
