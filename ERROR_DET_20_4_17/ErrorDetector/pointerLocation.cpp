#include "pointerLocation.h"



pointerLocation::pointerLocation()
{
	std::lock_guard<std::mutex> lk(mut);
}


pointerLocation::~pointerLocation()
{
}

int pointerLocation::getY()
{
	std::lock_guard<std::mutex> lk(mut);
	return yLocation;
}

int pointerLocation::getX()
{
	std::lock_guard<std::mutex> lk(mut);
	return xLocation;
}

void pointerLocation::pushSample(Sample sample)
{
	Sample* sampleToSubstruct;
	queue.push(sample);
	while (queue.size > 5) {
		queue.tryToPop(*sampleToSubstruct);
	}
	std::lock_guard<std::mutex> lk(mut);
	xLocation -= sampleToSubstruct->getValueX() / 5;
	xLocation += sample.getValueX() / 5;
	yLocation -= sampleToSubstruct->getValueY / 5;
	yLocation += sample.getValueY() / 5;	
}
