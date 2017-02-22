#include "TrackBar.h"

void TrackBar::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(line);
	target.draw(slider);
}

TrackBar::TrackBar(int x, int y, int width, int sections)
{
	create(x, y, width, sections);
}

void TrackBar::create(int x, int y, int width, int sections)
{
	this->x = x; this->y = y;
	this->width = width;
	this->height = 20;
	this->sections = sections;

	line.setSize(Vector2f(width, 3));
	line.setPosition(x, y-2);
	line.setFillColor(Color(127, 127, 127));

	slider.setSize(Vector2f(9, 20));
	slider.setOrigin(5, 10);
	slider.setPosition(x, y);
	slider.setFillColor(Color(0, 122, 204));
}

void TrackBar::handle(RenderWindow * win)
{
	Vector2u winSize = win->getSize();
	Vector2i p = Mouse::getPosition(*win);
	RectangleShape mouseCatcher(Vector2f(width, 20));
	mouseCatcher.setPosition(x, y-10);

	if (mouseCatcher.getGlobalBounds().contains(p.x, p.y))
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			slider.setPosition(p.x, y);
		}
	}
}

int TrackBar::getState()
{
	float multiplier = (float)width / (float)sections;
	for (int i = sections; i > 0; i--)
	{
		if (slider.getPosition().x > x+i*multiplier)
			return i;
	}
	return 0;
}

void TrackBar::setLineColor(Color color)
{
	line.setFillColor(color);
}

void TrackBar::setSliderColor(Color color)
{
	slider.setFillColor(color);
}

void TrackBar::setPosition(int x, int y)
{
	this->x = x; this->y = y;
	line.setPosition(x, y - 2);
	slider.setPosition(x, y);
	
}

void TrackBar::setSize(int width)
{
	slider.setPosition(1+x+((float)width/(float)sections)*(float)getState(), slider.getPosition().y);
	this->width = width;
	line.setSize(Vector2f(width, 3));
}

void TrackBar::setState(int state)
{
	float multiplier = (float)width / (float)sections;
	slider.setPosition(x + state*multiplier, y);
}

TrackBar::~TrackBar()
{
}
