#include "Button.h"
#include <iostream>

void Button::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(buttonSprite);
	target.draw(text);
}

Button::Button()
{
	create(0, 0, 100, 30, Text(), NULL, Color::White);
}

Button::Button(int x, int y, int width, int height, Text text, Font * f, Color color)
{
	create(x, y, width, height, text, f, color);
}

Button::Button(int x, int y, Text text, Font * f, std::string texturePath)
{
	create(x, y, text, f, texturePath);
}

void Button::create(int x, int y, int width, int height, Text text, Font * f, Color color)
{
	this->x = x; this->y = y;
	this->width = width; this->height = height;
	this->color = color;
	this->font = f;
	this->text = text;

	this->text.setFont(*font);
	this->text.setColor(Color::Black);

	buttonTexture.create(width, height);
	Uint8 *pixels = new Uint8[width*height * 4];
	for (int i = 0; i < width*height * 4; i += 4)
	{
		pixels[i] = 255;
		pixels[i + 1] = 255;
		pixels[i + 2] = 255;
		pixels[i + 3] = 255;
	}
	buttonTexture.update(pixels, width, height, 0, 0);
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setColor(this->color);
	buttonSprite.setPosition(x, y);

	this->text.setPosition(x + buttonSprite.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,
		y + buttonSprite.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2 - text.getCharacterSize() / 5);

	mouseOn = false;
	textured = false;
	buf.loadFromFile("res/sounds/click.wav");
	clickSound.setBuffer(buf);
	isActive = true;
	//clickSound.setVolume(SettingsManager::loadSoundsVolume());
}

void Button::create(int x, int y, Text text, Font * f, std::string texturePath)
{
	buttonTexture.loadFromFile(texturePath);
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setPosition(x, y);

	this->x = x; this->y = y;
	this->width = buttonSprite.getGlobalBounds().width;
	this->height = buttonSprite.getGlobalBounds().height;
	this->color = Color::White;
	this->font = f;
	this->text = text;

	this->text.setFont(*font);
	this->text.setColor(Color::Black);

	this->text.setPosition(x + buttonSprite.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,
		y + buttonSprite.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2 - text.getCharacterSize() / 5);

	mouseOn = false;
	textured = true;
	buttonSprite.setColor(Color::White);
	buf.loadFromFile("res/sounds/click.wav");
	clickSound.setBuffer(buf);
	isActive = true;
	//clickSound.setVolume(SettingsManager::loadSoundsVolume());
}

bool Button::click(Event * event, RenderWindow *win)
{
	if (buttonSprite.getGlobalBounds().contains(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y) && isActive)
	{
		if (event->type == Event::MouseButtonReleased)
		{
			if (event->mouseButton.button == Mouse::Left)
			{
				clickSound.play();
				return true;
			}
		}
	}
	return false;
}

bool Button::isMouseOn(RenderWindow *win)
{
	mouseOn = false;

	if (buttonSprite.getGlobalBounds().contains(Mouse::getPosition(*win).x, Mouse::getPosition(*win).y) && isActive)
	{
		mouseOn = true;
		if (color.r >= 10 && color.g >= 10 && color.b >= 10)
			buttonSprite.setColor(Color(color.r - 100, color.g - 100, color.b - 100));
		else
			buttonSprite.setColor(Color(color.r + 10,color.g + 10,color.b + 10));
		return true;
	}
	else if(isActive)
	{
		if (textured)
			buttonSprite.setColor(Color::White);
		else
			buttonSprite.setColor(this->color);
	}
	return false;
}

void Button::setColor(Color color)
{
	buttonSprite.setColor(color);
	this->color = color;
}

void Button::setTextColor(Color color)
{
	text.setColor(color);
}

void Button::setPosition(int x, int y)
{
	this->x = x; this->y = y;
	buttonSprite.setPosition(x, y);
	text.setPosition(x + buttonSprite.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,
		y + buttonSprite.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2 - text.getCharacterSize() / 5);
}

void Button::setSize(int width, int height)
{
	buttonSprite.scale((float)width / (float)this->width, (float)height / (float)this->height);
	this->width = width; this->height = height;
	text.setPosition(x + buttonSprite.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,
		y + buttonSprite.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2 - text.getCharacterSize() / 5);
}

void Button::setActive(bool state)
{
	if (state)
	{
		isActive = state;
		if (textured)
			buttonSprite.setColor(Color::White);
		else
			buttonSprite.setColor(this->color);
	}
	else
	{
		isActive = state;
		buttonSprite.setColor(Color(255,255,255,100));
	}
}

bool Button::getActive()
{
	return isActive;
}

void Button::setText(std::string text)
{
	this->text.setString(text);
	setPosition(x, y);
}

Button::~Button()
{
	text.setColor(color);
}
