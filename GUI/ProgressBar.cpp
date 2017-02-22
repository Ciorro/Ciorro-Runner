#include "ProgressBar.h"



void ProgressBar::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(border);
	target.draw(borderFill);
}

ProgressBar::ProgressBar()
{
	create(0,0,100,10,10);
}

ProgressBar::ProgressBar(int x, int y, int width, int height, int steps)
{
	create(x,y,width,height,steps);
}

void ProgressBar::create(int x, int y, int width, int height, int steps)
{
	this->x = x; this->y = y;
	this->width = width; this->height = height;
	this->steps = steps;
	this->value = 0;
	this->animate = true;

	border.setOutlineColor(Color(127, 127, 127));
	border.setOutlineThickness(2);
	border.setFillColor(Color(240, 240, 240));
	border.setPosition(x, y);
	border.setSize(Vector2f(width, height));

	borderFill.setFillColor(Color(21, 130, 48));
	borderFill.setPosition(x, y);
	borderFill.setSize(Vector2f(0, height));
}

bool ProgressBar::add()
{
	if (value < steps)
	{
		this->value++;
		update();
		return true;
	}
	return false;
}

bool ProgressBar::substract()
{
	if (value > 0)
	{
		this->value--;
		update();
		return true;
	}
	return false;
}

void ProgressBar::update()
{
	float value = (float)width / (float)steps;
	if (animate)
	{
		if (borderFill.getSize().x < value*this->value)
		{
			borderFill.setSize(Vector2f(borderFill.getSize().x + 1, height));
		}
		else
		{
			borderFill.setSize(Vector2f(borderFill.getSize().x - 1, height));
		}
	}
	else
		borderFill.setSize(Vector2f(value*this->value, height));
}

void ProgressBar::setBorderColor(Color color)
{
	border.setOutlineColor(color);
}

void ProgressBar::setFillColor(Color color)
{
	borderFill.setFillColor(color);
}

void ProgressBar::setPosition(int x, int y)
{
	this->x = x; this->y = y;
	border.setPosition(x, y);
	borderFill.setPosition(x, y);
}

void ProgressBar::setSize(int width, int height)
{
	this->width = width; this->height = height;
	border.setSize(Vector2f(width, height));
	update();
}

bool ProgressBar::setValue(int value)
{
	if (value <= steps)
	{
		this->value=value;
		update();
		return true;
	}
	return false;
}

void ProgressBar::setAnimation(bool animation)
{
	this->animate = animation;
}

void ProgressBar::setSteps(int steps)
{
	this->steps = steps;
}

ProgressBar::~ProgressBar()
{
}
