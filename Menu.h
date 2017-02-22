#pragma once
#include <SFML\Graphics.hpp>
#include "GUI\SfmlGui.h"
#include "Game.h"
#include "SettingsManager.h"
#include <SFML\Audio.hpp>
#include <Windows.h>
#include "Effects.h"
#include "ParticlesEmitter.h"
#include <SFML\Network.hpp>

using namespace sf;

class Menu
{
	RenderWindow win;
	Font font;
	Font arial;
	Texture menuBgTex;
	Sprite menuBg;
	Texture cursorTex;
	Sprite cursor;
	Music mainTheme;
	Game game;
	Effects effect;

	bool isUpdateAvailable;

	void selectPresetPack();
	void credits();
	void options();
	void selectLvl();
	void splahses();
	void joystickSteering();
	void controlSettings();
	void checkUpdates();
public:
	Menu();
	void init();
	void run();
	~Menu();
};

