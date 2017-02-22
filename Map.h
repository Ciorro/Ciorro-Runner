#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Chunk.h"
#include "Player.h"
#include "GUI\ProgressBar.h"
#include <SFML\Audio.hpp>
#include <Windows.h>
#include "ParticlesEmitter.h"
#include "Coin.h"
#include "EndlessChunkInfo.h"
#include "LightMap.h"

using namespace sf;

class Map:public Drawable
{
public:
	enum MapTheme { COUNTRYSIDE, CAVE };
private:
	std::string mapCode[15];
	std::vector <Chunk*> chunks;
	std::vector<int> sayingChunks;
	std::vector<std::string> texts;
	std::vector<Coin*> coins;
	std::vector<EndlessChunkInfo> endlessChunksInfo;
	std::vector<EndlessChunkInfo> usedChunks;

	RenderTexture chunksTargetTexture;
	Sprite chunksSprite;

	Texture backgroundTex;
	Sprite background[2];

	ProgressBar progress;
	Texture topbarTex;
	Sprite topbar;

	LightMap *lights;

	MapTheme mapTheme;

	size_t width;
	int totalNumberOfCoins;
	int numberOfCoins;
	int playerIntersectingChunk;

	bool isEndless;

	void draw(RenderTarget &target, RenderStates state)const;
public:
	float lenFromStart;
	bool isSlowMotionAvailable;
	unsigned int teleportsQuantity;
	float gameSpeed;
	Music music;
	Player player;

	Map(bool isEndless = false);
	void update();
	bool load(std::string path);
	int getNumberOfCoins();
	int getTotalNumberOfCoins();
	~Map();
};

