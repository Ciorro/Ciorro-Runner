#include "DropDownList.h"
#include <iostream>

void DropDownList::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(background);
	target.draw(text);
	target.draw(expandSquare, 4, Quads);
	target.draw(expandArrow, 3, Triangles);
	if(expanded)
		for (int i = 0; i < options.size(); i++)
			target.draw(options[i]);
	
}

DropDownList::DropDownList()
{
	create(0, 0, 100, 30, NULL);
}

DropDownList::DropDownList(int x, int y, int width, int height, Font * f)
{
	create(x, y, width, height, f);
}

void DropDownList::create(int x, int y, int width, int height, Font * f)
{
	this->x = x; this->y = y;
	this->width = width; this->height = height;
	this->font = f;

	background.setSize(Vector2f(width, height));
	background.setPosition(x, y);
	background.setFillColor(Color(240, 240, 240));
	background.setOutlineColor(Color(127, 127, 127));
	background.setOutlineThickness(1);

	expandSquare[0] = Vertex(Vector2f(x + width - height, y));
	expandSquare[1] = Vertex(Vector2f(x + width - height, y + height));
	expandSquare[2] = Vertex(Vector2f(x + width, y + height));
	expandSquare[3] = Vertex(Vector2f(x + width, y));

	for (int i = 0; i < 4; i++)
		expandSquare[i].color = Color(127, 127, 127);

	expandArrow[0] = Vertex(Vector2f(x + width - ((height / 4) * 3), y + height / 4));
	expandArrow[2] = Vertex(Vector2f(x + width - height / 2, y + height -height/ 4));
	expandArrow[1] = Vertex(Vector2f(x + width - height / 4, y + height / 4));

	for (int i = 0; i < 3; i++)
		expandArrow[i].color = Color(35, 35, 35);

	text.setColor(Color::Black);
	text.setFont(*this->font);
	text.setPosition(x + 2, y + 2);
	text.setCharacterSize(height / 2);

	currentId = 1;
}

void DropDownList::setOptions(std::vector<std::wstring> name)
{
	for (int i = 0; i < name.size(); i++)
	{
		Text t(name[i], *font, 0);
		currentName[currentName.size()] = name[i];
		Option option(options.size() + 1, x, y + height*(options.size() + 1), width, height, t, font);
		options.push_back(option);
	}
	text.setString(currentName[0]);
}

int DropDownList::handle(Event * event, RenderWindow *win)
{
	int clicked = 0;
	if (background.getGlobalBounds().contains(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y))
	{
		if (event->type == Event::MouseButtonReleased)
		{
			if (event->mouseButton.button == Mouse::Left)
			{
				expanded = true;
				background.setSize(Vector2f(width, height*(options.size() + 1)));
			}
		}
	}
	else
	{
		if (event->type == Event::MouseButtonReleased)
		{
			expanded = false;
			background.setSize(Vector2f(width, height));
		}
	}

	if (expanded)
	{
		for (int i = 0; i < options.size(); i++)
		{
			if (options[i].mouseOn(win))
			{
				if (clicked = options[i].click(event))
				{
					expanded = false;
					text.setString(currentName[clicked-1]);
					currentId = clicked;
					background.setSize(Vector2f(width, height));
				}
			}
		}
	}
	return clicked;
}

int DropDownList::getCurrentOption()
{
	return currentId;
}

void DropDownList::setOptionColor(Color color)
{
	for (size_t i = 0; i < options.size(); i++)
		options[i].setColor(color);
	background.setFillColor(color);
}

void DropDownList::setOptionHoverColor(Color color)
{
	for (size_t i = 0; i < options.size(); i++)
		options[i].setHoverColor(color);
}

void DropDownList::setOptionTextColor(Color color)
{
	text.setColor(color);
	for (size_t i = 0; i < options.size(); i++)
		options[i].setTextColor(color);
}

void DropDownList::setOptionHoverTextColor(Color color)
{
	for (size_t i = 0; i < options.size(); i++)
		options[i].setHoverTextColor(color);
}

void DropDownList::setBorderColor(Color color)
{
	background.setOutlineColor(color);
	for (int i = 0; i < 4; i++)
		expandSquare[i].color = color;
}

void DropDownList::setExpandArrowColor(Color color)
{
	for (int i = 0; i < 3; i++)
		expandArrow[i].color = color;
}

void DropDownList::setPosition(int x, int y)
{
	this->x = x; this->y = y;
	background.setPosition(x, y);

	expandSquare[0].position = Vector2f(x + width - height, y);
	expandSquare[1].position = Vector2f(x + width - height, y + height);
	expandSquare[2].position = Vector2f(x + width, y + height);
	expandSquare[3].position = Vector2f(x + width, y);

	expandArrow[0].position = Vector2f(x + width - ((height / 4) * 3), y + height / 4);
	expandArrow[2].position = Vector2f(x + width - height / 2, y + height - height / 4);
	expandArrow[1].position = Vector2f(x + width - height / 4, y + height / 4);

	text.setPosition(x + 2, y + 2);

	for (size_t i = 0; i < options.size(); i++)
		options[i].setPosition(x, y + height*(i + 1));
}

void DropDownList::setSize(int width, int height)
{
	this->width = width; this->height = height;
	background.setSize(Vector2f(width, height));
	text.setCharacterSize(height / 2);

	expandSquare[0].position = Vector2f(x + width - height, y);
	expandSquare[1].position = Vector2f(x + width - height, y + height);
	expandSquare[2].position = Vector2f(x + width, y + height);
	expandSquare[3].position = Vector2f(x + width, y);

	expandArrow[0].position = Vector2f(x + width - ((height / 4) * 3), y + height / 4);
	expandArrow[2].position = Vector2f(x + width - height / 2, y + height - height / 4);
	expandArrow[1].position = Vector2f(x + width - height / 4, y + height / 4);

	for (size_t i = 0; i < options.size(); i++)
		options[i].setSize(width, height);
	for (size_t i = 0; i < options.size(); i++)
		options[i].setPosition(x, y + height*(i + 1));
}

void DropDownList::setState(int state)
{
	text.setString(currentName[state - 1]);
	currentId = state;
}

DropDownList::~DropDownList()
{
}

