

#include "ThreadSafeQueue.hpp"
#include "TestParameters.h"
#include <fstream>
#include <iostream>


#define EVENT_PREFIX "EVENT:"

typedef unsigned short WCHAR;

class LogModule
{
private:

	ThreadSafeQueue<std::string> _logQueue;

	std::fstream _logFileStram;

	std::string _logFileName;

	/*
	*Coordinates of the rectangle on the screen.
	*/
	int _rectXpos = 0;
	int _rectYpos = 0;

public:

	/**
	*
	*
	*/
	LogModule(const char* logFileName);

	/**
	*
	*
	*/
	~LogModule();

	/**
	*
	*
	*/
	void setRectCoordinates(int x, int y);

	/**
	*
	*
	*/
	bool tryToPop();

	/**
	*
	*
	*/
	void waitAndPop();


	/**
	*
	*
	*/
	std::string createLogString(WCHAR jPosX, WCHAR jPosY, long sampleDuration);

	/**
	*
	*
	*/
	void pushLogEvent(std::string eventDiscription);

	/**
	*
	*
	*/
	void pushLogEntery(std::string eventDiscription);

	/**
	*
	*
	*/
	void createLogFileTitle(TestParameters& testParams);

	/**
	*
	*
	*/
	int writeStrToFile(std::string strToWrite);

};