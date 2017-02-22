#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Control
{
protected:
	int x, y;
	int width, height;
public:
	Vector2i getPosition();
	FloatRect getGlobalBounds();

};
