#pragma once
#include "Control.h"
#include <corecrt_wstring.h>

using namespace sf;

class CheckBox :public Control,public Drawable
{
	RectangleShape checkBoxShape;
	Font *font;
	Text description;
	bool checked;
	Vertex xSign[4];
	void draw(RenderTarget &target, RenderStates state)const;
public:
	CheckBox();
	CheckBox(int x, int y, Text description, Font *f, bool checked = 0);
	void create(int x, int y, Text description, Font *f, bool checked = 0);
	bool check(Event *event,RenderWindow *win);
	bool getStatus();
	void setString(std::wstring text);
	void setStatus(bool status);
	void setFillColor(Color color);
	void setBorderColor(Color color);
	void setTextColor(Color color);
	void setXColor(Color color);
	void setPosition(int x, int y);
	~CheckBox();
};

