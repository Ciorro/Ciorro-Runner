#include "Block.h"

Texture Block::blockTex = Texture();
SoundBuffer Block::blockBreakBuf;
Sound Block::blockBreakSnd;

void Block::draw(RenderTarget & target, RenderStates state) const
{
	if(!isAir)
		target.draw(block);
	if(Keyboard::isKeyPressed(Keyboard::D) && (isColliding==YES || spikes))
		target.draw(deathSurface);
	target.draw(*particles);
}

Block::Block(std::string blockId)
{
	std::string id;
	std::string subId;
	//Checking id
	int i = 0;
	while (blockId[i] != ':')
	{
		id += blockId[i];
		i++;
	}
	i++;
	//Checking sub id
	for (i; i < blockId.length(); i++)
	{
		subId += blockId[i];
	}
	//Is collidable?
	if (id == '0')
	{
		isColliding = YES;
	}
	else 
	{
		isColliding = NO;
	}
	//Is air?
	if (id == '1')
	{
		isAir = true;
	}
	else
	{
		isAir = false;
	}
	//Is winning?
	if (id == '2')
	{
		isWinning = true;
	}
	else
	{
		isWinning = false;
	}
	//Is spike?
	if (id == '3')
	{
		spikes = true;
	}
	else
	{
		spikes = false;
	}
	//is destroyable?
	if (id == '7')
	{
		destroyable = true;
		isColliding = YES;
	}
	else
	{
		destroyable = false;
	}
	//Setting texture
	block.setTexture(blockTex);
	block.setTextureRect(IntRect(stoi(subId) * 70, stoi(id) * 70, 70, 70));

	this->id = stoi(id);
	this->subId = stoi(subId);
	//Height of death square
	if (spikes)
	{
		deathSurface.setSize(Vector2f(70, 50));
	}
	else
	{
		deathSurface.setSize(Vector2f(70,39));
	}
	

	deathSurface.setFillColor(Color::Transparent);
	deathSurface.setOutlineColor(Color::Red);
	deathSurface.setOutlineThickness(2);

	particles = new ParticlesEmitter(ParticlesEmitter::EXPLOSION);
	particles->addColor(Color(102, 51, 0));
	particles->setParticleLifeTime(1);
	particles->quantity = 0;
	
	blockTex.setSmooth(true);
}

void Block::loadAssets(std::string path)
{
	blockTex.loadFromFile(path);
	blockBreakBuf.loadFromFile("res/sounds/blockbreak.wav");
	blockBreakSnd.setBuffer(blockBreakBuf);
	blockBreakSnd.setVolume(SettingsManager::loadSoundsVolume());
}

FloatRect Block::getGlobalBounds()
{
	return block.getGlobalBounds();
}

FloatRect Block::getDeathSquare()
{
	return deathSurface.getGlobalBounds();
}

bool Block::isCollidable()
{
	return isColliding;
}

bool Block::isBlockWinning()
{
	return isWinning;
}

bool Block::isSpike()
{
	return spikes;
}

bool Block::isDestroyable()
{
	return destroyable;
}

void Block::destroy()
{
	isColliding = NO;
	isAir = true;
	block.setColor(Color::Transparent);
	blockBreakSnd.play();
	for (int i = 0; i < 50; i++)
	{
		particles->addNewParticles();

	}
}

void Block::setPosition(int x, int y)
{
	block.setPosition(x, y);
	if (spikes)
	{
		deathSurface.setPosition(x, y+20);
	}
	else
	{
		deathSurface.setPosition(x, y+31);
	}
}

Vector2f Block::getPosition()
{
	return block.getPosition();
}

void Block::move(int x, int y)
{
	block.move(x, y);
	deathSurface.move(x, y);
	particles->setPosition(block.getPosition().x + 35, block.getPosition().y + 35);
	particles->update();
}

int Block::getId()
{
	return id;
}

int Block::getSubId()
{
	return subId;
}

Block::~Block()
{
}
