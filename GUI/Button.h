#pragma once
#include "Control.h"
#include <Windows.h>
#include <corecrt_wstring.h>
#include <SFML\Audio.hpp>
#include "../SettingsManager.h"

#ifndef BUTTON_H

using namespace sf;

class Button :public Control, public Drawable
{
	Texture buttonTexture;
	Sprite buttonSprite;
	Text text;
	Color color;
	Font *font;
	SoundBuffer buf;
	Sound clickSound; 
	bool mouseOn;
	bool textured;
	bool isActive;

	void draw(RenderTarget &target, RenderStates state)const;
public:
	Button();
	Button(int x, int y, int width, int height, Text text, Font *f, Color color=Color(240,240,240));
	Button(int x, int y, Text text, Font *f, std::string texturePath);
	void create(int x, int y, int width, int height, Text text, Font *f, Color color=Color(240,240,240));
	void create(int x, int y, Text text, Font *f, std::string texturePath);
	bool click(Event *event, RenderWindow *win);
	bool isMouseOn(RenderWindow *win);
	void setColor(Color color);
	void setTextColor(Color color);
	void setPosition(int x, int y);
	void setSize(int width, int height);
	void setActive(bool state);
	bool getActive();
	void setText(std::string text);
	~Button();
};

#endif // !BUTTON_H