#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;

class AnimatedObject:public Drawable, public Transformable
{
	unsigned short frame;
	unsigned short framesQuantity;
	unsigned int startingFrame;
	Vector2i frameSize;
	double frameTime;

	Clock frameTimer;

	Texture objectTexture;
	Sprite object;

	void draw(RenderTarget &target, RenderStates state)const;

public:
	AnimatedObject();
	AnimatedObject(std::string path, unsigned short framesQuantity, Vector2i frameSize, double frameTime,unsigned short startingFrame=0);
	void create(std::string path, unsigned short framesQuantity, Vector2i frameSize, double frameTime, unsigned short startingFrame = 0);
	void update();
	void move(float x, float y);
	void setStartingFrame(unsigned int frame);
	void setFrame(unsigned int frame);
	void setFrameTime(double time);
	FloatRect getGlobalBounds();
	~AnimatedObject();
};

