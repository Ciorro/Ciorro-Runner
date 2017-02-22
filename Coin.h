#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimatedObject.h"
#include "SettingsManager.h"

using namespace sf;

class Coin: public Drawable
{
	AnimatedObject objectCoin;
	SoundBuffer coinBuffer;
	Sound coinSound;

	void draw(RenderTarget &target, RenderStates state)const;
public:
	Coin(int chunk, int x, int y);
	void update();
	bool checkBounds(FloatRect bounds);
	void move(int x);
	~Coin();
};

