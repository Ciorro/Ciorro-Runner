#pragma once
#include "Control.h"

using namespace sf;

class TrackBar :public Control,public Drawable
{
	int sections;

	int width;
	RectangleShape line;
	RectangleShape slider;
	void draw(RenderTarget &target, RenderStates state)const;
public:
	TrackBar(int x = 0, int y = 0, int width = 100, int sections = 100);
	void create(int x, int y, int width, int sections = 100);
	void handle(RenderWindow *win);
	int getState();
	void setLineColor(Color color);
	void setSliderColor(Color color);
	void setPosition(int x, int y);
	void setSize(int width);
	void setState(int state);
	~TrackBar();
};

