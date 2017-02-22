#include "AnimatedObject.h"

void AnimatedObject::draw(RenderTarget & target, RenderStates state) const
{
	state.transform *= getTransform();
	target.draw(object, state);
}

AnimatedObject::AnimatedObject()
{
}

AnimatedObject::AnimatedObject(std::string path, unsigned short framesQuantity, Vector2i frameSize, double frameTime, unsigned short startingFrame)
{
	create(path, framesQuantity, frameSize, frameTime, startingFrame);
}

void AnimatedObject::create(std::string path, unsigned short framesQuantity, Vector2i frameSize, double frameTime, unsigned short startingFrame)
{
	this->framesQuantity = framesQuantity;
	this->frameSize = frameSize;
	this->frame = startingFrame;
	this->frameTime = frameTime;
	this->startingFrame = startingFrame;

	objectTexture.loadFromFile(path);
	object.setTexture(objectTexture);
	object.setTextureRect(IntRect(startingFrame*frameSize.x, 0, frameSize.x, frameSize.y));
}

void AnimatedObject::update()
{
	if (frameTimer.getElapsedTime().asMilliseconds() > frameTime)
	{
		object.setTextureRect(IntRect(frame*frameSize.x, 0, frameSize.x, frameSize.y));
		frame++;
		if (frame >= framesQuantity)
			frame = startingFrame;
		frameTimer.restart();
	}
}

void AnimatedObject::move(float x, float y)
{
	object.move(x, y);
}

void AnimatedObject::setStartingFrame(unsigned int frame)
{
	startingFrame = frame;
}

void AnimatedObject::setFrame(unsigned int frame)
{
	object.setTextureRect(IntRect(frame*frameSize.x, 0, frameSize.x, frameSize.y));
	this->frame=frame;
	frameTimer.restart();
}

void AnimatedObject::setFrameTime(double time)
{
	frameTime = time;
}

FloatRect AnimatedObject::getGlobalBounds()
{
	return object.getGlobalBounds();
}

AnimatedObject::~AnimatedObject()
{
}
