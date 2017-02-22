#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class ScrollingBackground :public Drawable
{
	Texture texture;
	Sprite sprite[2];

	float speed;

	void draw(RenderTarget &target, RenderStates state)const;
public:
	ScrollingBackground();
	ScrollingBackground(std::string path);
	void setTexture(std::string path);
	void update();
	void setSpeed(float speed)
	{
		this->speed = speed;
	}
	float getSpeed()
	{
		return speed;
	}
};

