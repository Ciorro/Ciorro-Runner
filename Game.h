#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>
#include "GUI\Button.h"
#include "GUI\ProgressBar.h"
#include "Map.h"
#include "Block.h"
#include "SettingsManager.h"

using namespace sf;

class Game
{
	class Pause:public Drawable
	{
		Text header;
		Text tip;
		Button exitGame;
		RectangleShape background;
		Texture gameBgTex;
		Sprite gameBg;
		RenderWindow *win;

		void draw(RenderTarget &target, RenderStates state)const;
	public:
		Pause(RenderWindow *win, Font *font);
		bool handle(Event *event);
		~Pause();
	};

	enum GAMESTATE { Continues, Ended, Won, Aborted };
	GAMESTATE gameState;

	RenderWindow *win;
	Event event;
	Pause *pauseMenu;
	Font *font;

	Texture cursorTex;
	Sprite cursor;
	Texture slowTex;
	Sprite slowmotion;
	Texture numberOfSlowmoTex;
	Sprite numberOfSlowmoBg;
	Texture numberOfCoinsTex;
	Sprite numberOfCoinsBg;

	Text fpsCounter;
	Text slowmoInfo;
	Text coinsInfo;
	Text lenFromStart;

	View view;
	Map *map;
	std::string mapPath;
	std::string themePath;
	Clock fpsClock;
	Clock teleportTime;
	ProgressBar teleportTimeProgress;
	int fps = 0;
	int lvlNumber;
	void gameOverScreen();
	void winScreen();
	void render();
	void handleEvents();
	void makeScreenshot();

	bool isEndless;
	bool teleportMode;
	bool pause;
	bool gameResult;
public:
	Game();
	void init(RenderWindow *win, Font *font, std::string mapName, int lvlNumber, bool isEndless = false);
	bool run();
	~Game();
};

