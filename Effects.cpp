#include "Effects.h"


void Effects::draw(RenderTarget & target, RenderStates state) const
{
	if(effectType!=NONE)
		target.draw(darkEffect);
}

Effects::Effects(int winx, int winy)
{
	darkEffect.setSize(Vector2f(winx, winy));
	effectType = NONE;
}

Effects::Effects()
{
	darkEffect.setSize(Vector2f(0,0));
	effectType = NONE;
}

void Effects::setEffectSize(int winx, int winy)
{
	darkEffect.setSize(Vector2f(winx, winy));
}

void Effects::startEffect(EFFECT_TYPE effect)
{
	effectType = effect;
	state = CONTINUES;
	if (effectType == Effects::FADE_IN)
	{
		darkEffect.setFillColor(Color::Black);
	}
	else if (effectType == Effects::FADE_OUT)
	{
		darkEffect.setFillColor(Color::Transparent);
	}

}

void Effects::stopEffect()
{
	state = WAITING;
	effectType = NONE;
}

Effects::STATE Effects::update()
{
	if (state == CONTINUES)
	{
		if (effectType == Effects::FADE_IN)
		{
			darkEffect.setFillColor(Color(0, 0, 0, darkEffect.getFillColor().a - 17));
			if (darkEffect.getFillColor().a == 0)
				state = ENDED;
		}
		if (effectType == Effects::FADE_OUT)
		{
			darkEffect.setFillColor(Color(0, 0, 0, darkEffect.getFillColor().a + 17));
			if (darkEffect.getFillColor().a == 255)
				state = ENDED;
		}
	}
	//printf("Grg");
	return state;
}

Effects::~Effects()
{
}
