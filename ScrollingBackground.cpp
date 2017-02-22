#include "ScrollingBackground.h"



void ScrollingBackground::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(sprite[0]);
	target.draw(sprite[1]);
}

ScrollingBackground::ScrollingBackground()
{
}

ScrollingBackground::ScrollingBackground(std::string path)
{
	setTexture(path);
}

void ScrollingBackground::setTexture(std::string path)
{
	texture.loadFromFile(path);
	sprite[0].setTexture(texture);
	sprite[1].setTexture(texture);
	sprite[1].move(sprite[1].getGlobalBounds().width, 0);
}

void ScrollingBackground::update()
{
	for (int i = 0; i < 2; i++)
	{
		if (sprite[i].getPosition().x <= -sprite[i].getGlobalBounds().width)
		{
			sprite[i].move(sprite[i].getGlobalBounds().width * 2, 0);
		}
		sprite[i].move(speed, 0);
	}
}