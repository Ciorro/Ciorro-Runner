#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Effects:public Drawable
{
public:
	enum EFFECT_TYPE { NONE, FADE_IN, FADE_OUT };
	enum STATE { CONTINUES, ENDED, WAITING };
private:
	EFFECT_TYPE effectType;
	STATE state;
	RectangleShape darkEffect;
	void draw(RenderTarget &target, RenderStates state)const;
	Clock effectTime;
public:
	Effects(int winx,int winy);
	Effects();
	void setEffectSize(int winx, int winy);
	void startEffect(EFFECT_TYPE effect);
	void stopEffect();
	STATE update();
	~Effects();
};

