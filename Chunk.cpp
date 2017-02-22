#include "Chunk.h"
#include <iostream>


void Chunk::draw(RenderTarget & target, RenderStates state) const
{
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		RectangleShape chunkBorders(Vector2f(1680,1050));
		chunkBorders.setFillColor(Color::Transparent);
		chunkBorders.setOutlineColor(Color::Blue);
		chunkBorders.setOutlineThickness(1);
		chunkBorders.setPosition(blocks[0]->getPosition());
		target.draw(chunkBorders);
	}
}

Chunk::Chunk(std::string mapCode[])
{	
	for (int i = 0; i < 15; i++)
	{
		int iteration = 0;
		for (int j = 0; j < 24; j++)
		{
			std::string id;
			
			while (mapCode[i][iteration]!=' ')
			{
				id += mapCode[i][iteration];
				iteration++;
			}
			iteration++;
			blocks.push_back(new Block(id));
			//std::cout << i*j << "/" << 15 * 24 << std::endl;
		}
		mapCode[i].erase(0, iteration);
	}
	int x = 0, y = 0;
	for (size_t i = 0; i < blocks.size(); i++)
	{
		blocks[i]->setPosition(x, y);
		x += 70;
		if (x >= 1680)
		{
			x = 0;
			y += 70;
		}
	}
}

void Chunk::setPosition(int baseX, int baseY)
{
	int x = baseX;
	int y = baseY;
	for (size_t i = 0; i < blocks.size(); i++)
	{
		blocks[i]->setPosition(x, y);
		x += 70;
		if (x >= baseX+1680)
		{
			x = baseX;
			y += 70;
		}
	}
}

void Chunk::move(int x, int y)
{
	for (size_t i = 0; i < blocks.size(); i++)
	{
		blocks[i]->move(x, y);
	}
}

void Chunk::drawOnTexture(RenderTexture * tex)
{
	for (size_t i = 0; i < blocks.size(); i++)
	{
		tex->draw(*blocks[i]);
	}
}

FloatRect Chunk::getGlobalBounds()
{
	//For 1680x1050
	return FloatRect(blocks[0]->getPosition(),Vector2f(1680,1050));
}

std::vector<Block*> Chunk::getBlocks()
{
	return blocks;
}

Block * Chunk::getBlockAt(int x, int y)
{
	for (size_t i = 0; i < blocks.size(); i++)
	{
		if (blocks[i]->getGlobalBounds().contains(x, y))
		{
			return blocks[i];
		}
	}
	return nullptr;
}

Chunk::~Chunk()
{
	for (size_t i = 0; i < blocks.size(); i++)
	{
		delete blocks[i];
		blocks[i] = NULL;
	}

	blocks.clear();
	std::vector<Block*>().swap(blocks);
}
