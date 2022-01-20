#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
private:
	Time duration;
	Time timeForFrame;
	Time currTime;
	int numOfFrames;
	int currFrameIndex;
	IntRect currFrame;
public:
	Animation();
	void setup(int frameNum, int textureWidth, int textureWeight, Time dur);
	const IntRect& update(Time dtTime);
	void reset();
	~Animation();
};

