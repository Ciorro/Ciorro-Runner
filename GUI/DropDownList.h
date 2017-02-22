#pragma once
#include "Control.h"
#include <corecrt_wstring.h>
#include <vector>
#include <map>
#include "Option.h"

using namespace sf;

class DropDownList :public Control, public Drawable
{
	bool expanded;
	RectangleShape background;
	Vertex expandSquare[4];
	Vertex expandArrow[3];

	std::vector<Option> options;
	std::map<int, std::wstring> currentName;
	int currentId;
	Font *font;
	Text text;
	void draw(RenderTarget &target, RenderStates state)const;
public:
	DropDownList();
	DropDownList(int x,int y,int width,int height,Font *f);
	void create(int x, int y, int width, int height, Font *f);
	void setOptions(std::vector<std::wstring> name);
	int handle(Event *event, RenderWindow *win);
	int getCurrentOption();
	void setOptionColor(Color color);
	void setOptionHoverColor(Color color);
	void setOptionTextColor(Color color);
	void setOptionHoverTextColor(Color color);
	void setBorderColor(Color color);
	void setExpandArrowColor(Color color);
	void setPosition(int x, int y);
	void setSize(int width, int height);
	void setState(int state);
	~DropDownList();
};

