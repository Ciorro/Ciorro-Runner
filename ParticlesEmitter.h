#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;

class ParticlesEmitter: public Drawable
{
public:
	enum Direction { LEFT, RIGHT, UP, DOWN, EXPLOSION };
private:

	class Particle : public Drawable
	{
		float x, y;
		float speedX, speedY;
		CircleShape particle;
		Clock lifeTime;

		void draw(RenderTarget &target, RenderStates state)const;
	public:
		float gravityPower;
		Particle(float speedX, float speedY, float x, float y, Color color);
		float getLifeTime();
		void update();
	};

	std::vector<Particle*> particles;
	std::vector<Color> colors;

	Vector2f directionX, directionY;
	Vector2f position;
	float power;
	float gravityPower;
	float particleLifeTime;

	Clock frequency;

	Direction direction;

	void draw(RenderTarget &target, RenderStates state)const;
public:
	float quantity;
	ParticlesEmitter(Direction direction);
	void update();
	void addNewParticles();
	void setPosition(float x, float y);
	void setPower(float power);
	void setGravityPower(float power=0.5);
	void setParticleLifeTime(float lifeTime);
	void addColor(Color color);
	void resetColors();
	~ParticlesEmitter();
};

