#pragma once
#include <SFML\Graphics.hpp>
#include "Control.h"

using namespace sf;

class Option :public Control, public Drawable
{
	RectangleShape optionBackground;
	Text text;
	Font *font;
	Color hover;
	Color color;
	Color textColor;
	Color hoverTextColor;

	int id;
	
	

	void draw(RenderTarget &target, RenderStates state)const;
public:
	Option(int id, int x, int y, int width, int height, Text text, Font *f);

	bool mouseOn(RenderWindow *win);
	int click(Event *event);
	void setPosition(int x, int y);
	
	void setColors(Color backgroundColor, Color hoverBackground, Color textColor, Color hoverTextColor);
	void setColor(Color color);
	void setHoverColor(Color color);
	void setTextColor(Color color);
	void setHoverTextColor(Color color);
	
	void setSize(int width, int height);
	Vector2f getPosition();
};