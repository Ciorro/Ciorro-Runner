#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;

class LightMap
{
public:
	enum COLOR{DARK_SLATE_BLUE, LEMON_CHIFFON};
private:
	Texture lightTex;
	RenderTexture lightMapTex;
	Sprite lightMap;
	Color color;
	std::vector<Sprite> light;
public:
	void draw(RenderWindow *win);
	void draw(RenderTarget &target);
	LightMap(Vector2f size, std::string pathToLightImage);
	int addLight(); //returns added light id in vector
	void setColor(Color color);
	void setColor(COLOR color);
	std::vector<Sprite>* getLightVector();
	~LightMap();
};

