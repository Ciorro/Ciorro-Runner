#include "CheckBox.h"
#include <iostream>


void CheckBox::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(checkBoxShape);
	target.draw(description);
	if(checked)
		target.draw(xSign, 4, Lines);
}



CheckBox::CheckBox()
{
	create(0, 0, Text(),NULL,false);
}

CheckBox::CheckBox(int x, int y, Text description, Font *f, bool checked)
{
	create(x, y, description, f, checked);
}

void CheckBox::create(int x, int y, Text description, Font * f, bool checked)
{
	this->checked = checked;
	this->x = x; this->y = y;
	this->description = description;
	this->font = f;

	this->description.setFont(*font);
	this->description.setPosition(x + description.getCharacterSize() + 10, y - description.getCharacterSize() / 5);
	this->description.setColor(Color::Black);

	checkBoxShape.setPosition(x, y);
	checkBoxShape.setSize(Vector2f(description.getCharacterSize(), description.getCharacterSize()));
	checkBoxShape.setFillColor(Color(240, 240, 240));
	checkBoxShape.setOutlineThickness(1);
	checkBoxShape.setOutlineColor(Color(100, 100, 100));

	xSign[0] = Vertex(Vector2f(x + 2, y + 2));
	xSign[1] = Vertex(Vector2f(x + description.getCharacterSize() - 2, y + description.getCharacterSize() - 2));
	xSign[2] = Vertex(Vector2f(x + description.getCharacterSize() - 2, y + 2));
	xSign[3] = Vertex(Vector2f(x + 2, y + description.getCharacterSize() - 2));
	for (int i = 0; i < 4; i++)
		xSign[i].color = Color::Black;
	this->width = description.getCharacterSize() + 10+ description.getGlobalBounds().width;
	this->height = checkBoxShape.getGlobalBounds().height;
}

bool CheckBox::check(Event * event, RenderWindow *win)
{
	if (checkBoxShape.getGlobalBounds().contains(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y))
	{
		if (event->type == Event::MouseButtonReleased)
		{
			if (event->key.code == Mouse::Left && !checked)
				checked = true;
			else if (event->key.code == Mouse::Left && checked)
				checked = false;
		}
	}
	return checked;
}

void CheckBox::setString(std::wstring text)
{
	description.setString(text);
}
void CheckBox::setStatus(bool status)
{
	checked = status;
}
void CheckBox::setFillColor(Color color)
{
	checkBoxShape.setFillColor(color);
}
void CheckBox::setBorderColor(Color color)
{
	checkBoxShape.setOutlineColor(color);
}
void CheckBox::setTextColor(Color color)
{
	description.setColor(color);
}
void CheckBox::setXColor(Color color)
{
	for (int i = 0; i < 4; i++)
		xSign[i].color = color;
}
void CheckBox::setPosition(int x, int y)
{
	this->x = x; this->y = y;
	checkBoxShape.setPosition(x, y);
	xSign[0].position = Vector2f(x + 2, y + 2);
	xSign[1].position = Vector2f(x + description.getCharacterSize() - 2, y + description.getCharacterSize() - 2);
	xSign[2].position = Vector2f(x + description.getCharacterSize() - 2, y + 2);
	xSign[3].position = Vector2f(x + 2, y + description.getCharacterSize() - 2);
	this->description.setPosition(x + description.getCharacterSize() + 10, y - description.getCharacterSize() / 5);
}
bool CheckBox::getStatus()
{
	return checked;
}

CheckBox::~CheckBox()
{
	font = NULL;
}
