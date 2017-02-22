#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "AnimatedObject.h"
#include <vector>
#include <iostream>
#include "SettingsManager.h"
#include "ParticlesEmitter.h"
#include "Chunk.h"

using namespace sf;

class Player:public Drawable
{
public:
	enum STATE { ON_AIR, ON_GROUND, IS_DEAD, IS_DONE, GOING_DOWN_FAST};
	enum THEME { COUNTRYSIDE, CAVE };
private:
	void draw(RenderTarget &target, RenderStates state)const;
	void move();

	AnimatedObject player;
	Texture playerOnAirTex;
	Sprite playerOnAir;
	Texture bubbleTex;
	Sprite bubbleLeft;
	Sprite bubbleRight;
	Sprite bubbleArrow;
	Sprite bubbleMiddle;
	Texture punchDownInfoTexture;
	Sprite punchDownInfo;
	Font sayFont;
	bool isSaying;
	bool canPunchDown;
	Text sayText;
	THEME theme;
	//physics
	STATE state;
	float speed;
	float horizontalSpeed;
	Chunk *chunk; // actual chunk
	//Sounds
	SoundBuffer jumpBuf;
	Sound jumpSnd;
	SoundBuffer impactFallBuf;
	Sound impactFall;

public:
	ParticlesEmitter *particles;

	Player(THEME theme = COUNTRYSIDE);
	void setTheme(THEME theme);
	void jump();
	void update(Chunk* chunk);
	STATE getState();
	void kill();
	void say(std::string text);
	FloatRect getGlobalBounds();
	void teleport(Vector2i mousePos);
	~Player();
};

