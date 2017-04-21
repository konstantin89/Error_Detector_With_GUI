#include "Sample.h"
#include "ThreadSafeQueue.hpp"
#ifndef POINTER_LOCATION
#define POINTER_LOCATION
class pointerLocation
{
private:
	ThreadSafeQueue<Sample> queue;
	int xLocation = 0;
	int yLocation = 0;
	int halfScreen = 300;
	int FACTOR_SIZE = 8;
	
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
	void setScreenSize(int screenLocation);
	~pointerLocation();
	int getY();
	int getX();
	void pushSample(Sample sample);
};
#endif

