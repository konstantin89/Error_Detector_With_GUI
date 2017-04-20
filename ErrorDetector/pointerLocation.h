#pragma once
#include "Error_Detector\Sample.h"
#include "Error_Detector\ThreadSafeQueue.hpp"
class pointerLocation
{
private:
	ThreadSafeQueue<Sample> queue;
	int xLocation;
	int yLocation;
	/*
	* Mutex for the thread safety.
	*/
	mutable std::mutex mut;

	/*
	* Condition variable for data extracting.
	*/
	std::condition_variable cond;                    

public:
	pointerLocation();
	~pointerLocation();
	int getY();
	int getX();
	void pushSample(Sample sample);
};

