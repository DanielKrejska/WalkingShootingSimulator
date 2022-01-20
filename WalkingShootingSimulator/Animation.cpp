#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::setup(int frameNum, int textureWidth, int textureHeight, Time dur)
{
	this->duration = dur;
	this->reset();
	currFrame.height = textureHeight;
	currFrame.width = textureWidth / frameNum;
	numOfFrames = frameNum;
	timeForFrame = seconds(dur.asSeconds() / frameNum);
}

void Animation::reset()
{
	currTime = Time::Zero;
	currFrame.top = currFrame.left = 0;
	currFrameIndex = 0;
}

const IntRect& Animation::update(Time dtTime)
{
	currTime += dtTime;
	if (currTime >= timeForFrame)
	{
		currTime = Time::Zero;
		currFrameIndex++;
		if (currFrameIndex >= numOfFrames)
		{
			currFrameIndex = 0;
		}
		currFrame.left = currFrameIndex * currFrame.width;
	}
	return currFrame;
}
