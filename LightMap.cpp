#include "LightMap.h"




void LightMap::draw(RenderWindow * win)
{
	lightMapTex.clear(color);
	BlendMode blend = BlendAdd;
	BlendMode blend2 = BlendMultiply;

	for (size_t i = 0; i < light.size(); i++)
	{
		lightMapTex.draw(light[i], blend);
	}
	lightMapTex.display();
	win->draw(lightMap, blend2);
}

void LightMap::draw(RenderTarget & target)
{
	lightMapTex.clear(color);
	BlendMode blend = BlendAdd;
	BlendMode blend2 = BlendMultiply;

	for (size_t i = 0; i < light.size(); i++)
	{
		lightMapTex.draw(light[i], blend);
	}
	lightMapTex.display();
	target.draw(lightMap, blend2);
}

LightMap::LightMap(Vector2f size, std::string pathToLightImage)
{
	lightMapTex.create(size.x, size.y);
	lightMap.setTexture(lightMapTex.getTexture());
	lightTex.loadFromFile(pathToLightImage);
	color = Color::White;
}

int LightMap::addLight()
{
	light.push_back(Sprite(lightTex));
	light.back().setOrigin(light.back().getGlobalBounds().width / 2, light.back().getGlobalBounds().height / 2);
	return light.size()-1;
}

void LightMap::setColor(Color color)
{
	this->color = color;
}

void LightMap::setColor(COLOR color)
{
	switch (color)
	{
	case DARK_SLATE_BLUE:
		this->color = Color(72, 61, 139);
		break;
	case LEMON_CHIFFON:
		this->color = Color(255, 250, 205);
		break;
	}
}

std::vector<Sprite>* LightMap::getLightVector()
{
	return &light;
}


LightMap::~LightMap()
{
}
