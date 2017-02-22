#include "Option.h"

void Option::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(optionBackground);
	target.draw(text);
}

Option::Option(int id, int x, int y, int width, int height, Text text, Font * f)
{
	color = Color(240, 240, 240);
	textColor = Color::Black;
	hover = Color(0, 122, 204);
	hoverTextColor = Color::White;

	this->x = x; this->y = y;
	this->width = width; this->height = height;
	this->font = f;
	this->text = text;

	optionBackground.setPosition(x, y);
	optionBackground.setSize(Vector2f(width, height));
	optionBackground.setFillColor(Color(240, 240, 240));

	this->text.setFont(*font);
	this->text.setCharacterSize(height / 2);
	this->text.setColor(Color::Black);
	this->text.setPosition(x + 2, y + 2);

	this->id = id;
}

bool Option::mouseOn(RenderWindow *win)
{
	if (optionBackground.getGlobalBounds().contains(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y))
	{
		optionBackground.setFillColor(hover);
		text.setColor(hoverTextColor);
		return true;
	}
	else
	{
		optionBackground.setFillColor(color);
		text.setColor(textColor);
	}
	return false;
}


int Option::click(Event * event)
{
	if (event->type == Event::MouseButtonReleased)
	{
		if (event->mouseButton.button == Mouse::Left)
			return id;
	}
	return 0;
}

void Option::setSize(int width, int height)
{
	this->width = width; this->height = height;
	optionBackground.setSize(Vector2f(width, height));
	this->text.setCharacterSize(height / 2);
}

Vector2f Option::getPosition()
{
	return Vector2f(optionBackground.getPosition());
}

void Option::setPosition(int x, int y)
{
	optionBackground.setPosition(x, y);
	this->text.setPosition(x + 2, y + 2);
	this->x = x; this->y = y;
}

void Option::setColors(Color backgroundColor, Color hoverBackground, Color textColor, Color hoverTextColor)
{
	setColor(backgroundColor);
	setHoverColor(hoverBackground);
	setTextColor(textColor);
	setHoverTextColor(hoverTextColor);
}

void Option::setColor(Color color)
{
	this->color = color;
}

void Option::setHoverColor(Color color)
{
	hover = color;
}

void Option::setTextColor(Color color)
{
	textColor = color;
}

void Option::setHoverTextColor(Color color)
{
	hoverTextColor = color;
}
