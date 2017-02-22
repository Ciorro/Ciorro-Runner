#include "ParticlesEmitter.h"



void ParticlesEmitter::draw(RenderTarget & target, RenderStates state) const
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		target.draw(*particles[i]);
	}
}

ParticlesEmitter::ParticlesEmitter(Direction direction)
{
	this->direction = direction;
	switch (direction)
	{
	case LEFT:
		directionX = { 5,-5 };
		directionY = { 2,-2 };
		break;
	case RIGHT:
		directionX = { 5,5 };
		directionY = { 2,-2 };
		break;
	case UP:
		directionX = { 5,-2.5 };
		directionY = { 10,-10 };
		break;
	case DOWN:
		directionX = { 5,-2.5 };
		directionY = { 10,10 };
		break;
	case EXPLOSION:
		directionX = { 20, -10 };
		directionY = { 20,-10 };
		break;
	}
	power = 1;
	particleLifeTime = 1;
	gravityPower = 0.5;
	quantity = 0.05;
}

void ParticlesEmitter::update()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		//std::cout << "G: " << gravityPower << std::endl;
		particles[i]->gravityPower = gravityPower;
		particles[i]->update();
		if (particles[i]->getLifeTime() > particleLifeTime)
		{
			particles.erase(particles.begin()+i);
		}
	}
}

void ParticlesEmitter::addNewParticles()
{
	if (frequency.getElapsedTime().asSeconds() > quantity && colors.size()>0)
	{
		int randomColorId = rand() % colors.size();
		float randomXSpeed = rand() % (int)directionX.x + (int)directionX.y;
		float randomYSpeed = rand() % (int)directionY.x + (int)directionY.y;
		particles.push_back(new Particle(randomXSpeed*power, randomYSpeed*power, position.x, position.y, colors[randomColorId]));
		frequency.restart();
	}
}

void ParticlesEmitter::setPosition(float x, float y)
{
	position = { x,y };
}

void ParticlesEmitter::setPower(float power)
{
	this->power = power;
}

void ParticlesEmitter::setGravityPower(float power)
{
	this->gravityPower = power;
}

void ParticlesEmitter::setParticleLifeTime(float lifeTime)
{
	particleLifeTime = lifeTime;
}

void ParticlesEmitter::addColor(Color color)
{
	colors.push_back(color);
}

void ParticlesEmitter::resetColors()
{
	colors.clear();
}

ParticlesEmitter::~ParticlesEmitter()
{
}

//********************************************
// PARTICLE
//********************************************

void ParticlesEmitter::Particle::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(particle);
}

ParticlesEmitter::Particle::Particle(float speedX, float speedY, float x, float y, Color color)
{
	this->speedX = speedX;
	this->speedY = speedY;
	gravityPower = 0.5;
	this->x = x;
	this->y = y;

	particle.setRadius(1.50);
	particle.setOrigin(2, 2);
	particle.setPosition(x, y);
	particle.setFillColor(color);
}

float ParticlesEmitter::Particle::getLifeTime()
{
	return lifeTime.getElapsedTime().asSeconds();
}

void ParticlesEmitter::Particle::update()
{
	x += speedX;
	y += speedY;
	
	speedY += gravityPower;
	if (speedX > 1)
	{
		speedX --;
	}
	else if (speedX < -1)
	{
		speedX++;
	}
	particle.setPosition(x, y);
}
