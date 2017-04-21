#ifndef PATTERN_H
#define PATTERN_H
#include <vector>


struct patternNode{
	int numOfFrames;
	float angle_x;
	float angle_y;
	int x_direction;
	int y_direction;
};

class Pattern
{
	
	patternNode aa{330,0.9,1.1, 1, -1};
	patternNode ab{380,1.3,0.7, -1,1};
	patternNode ac{410,0.47, 1.53, -1,-1};
	
	
	patternNode ba{300,1.0,1.0, -1,1};
	patternNode bb{600,1.3,0.7, -1,-1};
	patternNode bc{600,1.3,0.7, -1,1};
	patternNode bd{370,0.8,1.5, -1,-1};
	
	patternNode ca{400,1.0,1.0, 1,1};
	patternNode cb{400,0,2.0, 1,-1};
	patternNode cc{700,1.0,1.0, -1,-1};
	patternNode cd{600,0.6,1.6, 1,-1};
	patternNode ce{500,1.3,1.4, -1,-1};

	std::vector<patternNode> pattern;
	int currentIndex = 0;
public:
    Pattern();
    Pattern(int numOfEdges);
    float getNextAngleX();
    float getNextAngleY();
    bool update();
    int getNextCounter();
    int getXDir();
    int getYDir();
    void init(int numOfEdges);
    int PatternNumOfEdges = 3;
};

#endif // PATTERN_H
