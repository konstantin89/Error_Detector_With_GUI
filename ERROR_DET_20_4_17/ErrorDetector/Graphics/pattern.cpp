#include "pattern.h"

Pattern::Pattern()
{
	
}

Pattern::Pattern(int numOfEdges)
{
	PatternNumOfEdges = numOfEdges;
	/*for(int i = 0; i < numOfEdges; i++){
		pattern.push_back(patternNode());
	}*/
		switch(numOfEdges){
			case 3:
			pattern.push_back(aa);
			pattern.push_back(ab);
			pattern.push_back(ac);

			break;
			default:
			break;
		}
}

float Pattern::getNextAngleX(){
	return pattern[currentIndex].angle_x;
}

float Pattern::getNextAngleY(){
	return pattern[currentIndex].angle_y;
}

/*Function to update the current pattern node.
 * return - true if a'circle' complete.
 * */
bool Pattern::update(){
	currentIndex++;
	if(currentIndex == PatternNumOfEdges){
		currentIndex = 0;
		return true;
	}
	return false;
}

int Pattern::getNextCounter(){
	return pattern[currentIndex].numOfFrames;
}

int Pattern::getXDir(){
	return pattern[currentIndex].x_direction;
}

int Pattern::getYDir(){
	return pattern[currentIndex].y_direction;
}
void Pattern::init(int numOfEdges){
		PatternNumOfEdges = numOfEdges;
		switch(numOfEdges){
			case 3:
				pattern.push_back(aa);
				pattern.push_back(ab);
				pattern.push_back(ac);
			break;
			case 4:
				pattern.push_back(ba);
				pattern.push_back(bb);
				pattern.push_back(bc);
				pattern.push_back(bd);
			
			break;
			case 5:
				pattern.push_back(ca);
				pattern.push_back(cb);
				pattern.push_back(cc);
				pattern.push_back(cd);
				pattern.push_back(ce);
			break;
			default:
			break;
		}
}
