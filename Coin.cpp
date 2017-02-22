#include "Coin.h"

#include <iostream>

void Coin::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(objectCoin);
}

Coin::Coin(int chunk, int x, int y)
{
	objectCoin.create("res/textures/coin.png", 5, Vector2i(20,20), 50);
	//for 1680x1050 res and 70x70 block size
	std::cout << "coin: "<<(x * 70 + 10) + 1680 * chunk << "|" << y * 70 + 10 << std::endl;
	objectCoin.move((x*70+25)+1680*chunk, y*70+25);
	//loading sound
	coinBuffer.loadFromFile("res/sounds/coin.wav");
	coinSound.setBuffer(coinBuffer);
	coinSound.setVolume(SettingsManager::soundsVolume);
}

void Coin::update()
{
	objectCoin.update();
}

bool Coin::checkBounds(FloatRect bounds)
{
	if (bounds.intersects(objectCoin.getGlobalBounds()))
	{
		coinSound.play();
		return true;
	}
	return false;
}

void Coin::move(int x)
{
	objectCoin.move(x, 0);
}

Coin::~Coin()
{
}
