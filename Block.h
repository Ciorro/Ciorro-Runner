#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "ParticlesEmitter.h"
#include "SettingsManager.h"

using namespace sf;

class Block: public Drawable
{
	void draw(RenderTarget &target, RenderStates state)const;
	enum COLLIDING { NO, YES };
	COLLIDING isColliding;
	RectangleShape deathSurface;
	int id, subId;
	bool isWinning;
	bool spikes;
	bool isAir;
	bool destroyable;
	ParticlesEmitter *particles;

	static Texture blockTex;
	Sprite block;

	static SoundBuffer blockBreakBuf;
	static Sound blockBreakSnd;

public:
	Block(std::string id);
	static void loadAssets(std::string path);
	FloatRect getGlobalBounds();
	FloatRect getDeathSquare();
	bool isCollidable();
	bool isBlockWinning();
	bool isSpike();
	bool isDestroyable();
	void destroy();
	void setPosition(int x, int y);
	Vector2f getPosition();
	void move(int x, int y);
	int getId();
	int getSubId();
	~Block();
};

