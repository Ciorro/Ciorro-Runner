#pragma once
#include "Control.h"


using namespace sf;

class ProgressBar :public Control,public Drawable
{
	RectangleShape border;
	RectangleShape borderFill;
	int value;
	int steps;
	void draw(RenderTarget &target, RenderStates state)const;
	bool animate;
public:
	void update();
	ProgressBar();
	ProgressBar(int x, int y, int width, int height, int steps);
	void create(int x, int y, int width, int height, int steps);
	bool add();
	bool substract();
	void setBorderColor(Color color);
	void setFillColor(Color color);
	void setPosition(int x, int y);
	void setSize(int width, int height);
	bool setValue(int value);
	void setAnimation(bool animation);
	void setSteps(int steps);
	~ProgressBar();
};
