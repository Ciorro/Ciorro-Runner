#pragma once
#include "Control.h"

Vector2i Control::getPosition()
{
	return Vector2i(x, y);
}

FloatRect Control::getGlobalBounds()
{
	return FloatRect(x, y, width, height);
}