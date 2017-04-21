#include "pointerLocation.h"
#define SIZE_OF_QUEUE 20



pointerLocation::pointerLocation()
{
	std::lock_guard<std::mutex> lk(mut);
}

void pointerLocation::setScreenSize(int screenLocation)
{
	halfScreen = (int)(screenLocation/2);
	int screenSizeFactor = (int)(halfScreen/300) ;
	screenSizeFactor += 1;
	this->FACTOR_SIZE = (int)(8 / screenSizeFactor);
}

pointerLocation::~pointerLocation()
{
}

int pointerLocation::getY()
{
	std::lock_guard<std::mutex> lk(mut);
	return   pointerLocation::halfScreen + yLocation/pointerLocation::FACTOR_SIZE;
}

int pointerLocation::getX()
{
	std::lock_guard<std::mutex> lk(mut);
	return pointerLocation::halfScreen + xLocation/pointerLocation::FACTOR_SIZE;
}

void pointerLocation::pushSample(Sample sample)
{
	Sample sampleToSubstruct;
	queue.push(sample);
	while (queue.size() > SIZE_OF_QUEUE) {
		queue.tryToPop(sampleToSubstruct);
		std::lock_guard<std::mutex> lk(mut);
		xLocation -= (sampleToSubstruct.getValueX() / SIZE_OF_QUEUE);
		xLocation += (sample.getValueX() / SIZE_OF_QUEUE);
		yLocation -= (sampleToSubstruct.getValueY() / SIZE_OF_QUEUE);
		yLocation += (sample.getValueY() / SIZE_OF_QUEUE);
	}
	
}
