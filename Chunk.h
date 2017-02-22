#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Block.h"

using namespace sf;

class Chunk :public Drawable
{
	std::vector<Block*> blocks;
	void draw(RenderTarget &target, RenderStates state)const;
public:
	Chunk(std::string[]);
	void setPosition(int x, int y);
	void move(int x, int y);
	void drawOnTexture(RenderTexture *tex);
	FloatRect getGlobalBounds();
	std::vector<Block*> getBlocks();
	Block *getBlockAt(int x, int y);
	~Chunk();
};

