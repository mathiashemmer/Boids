#include "Particle.h"

Particle::Particle()
{
	this->radius = 1;
	this->position = Vector2(0, 0);
	this->velocity = Vector2(0, 0);
	this->acceleration = Vector2(0, 0);
}

Particle::Particle(unsigned int radius)
{
	this->radius = radius;
	this->position = Vector2(0, 0);
	this->velocity = Vector2(0, 0);
	this->acceleration = Vector2(0, 0);
}

Particle::Particle(unsigned int radius, Vector2 position)
{
	this->radius = radius;
	this->position = Vector2(position.x, position.y);
	this->velocity = Vector2(0, 0);
	this->acceleration = Vector2(0, 0);
}
