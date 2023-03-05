#include "Vector2.h"

#pragma once
class Particle
{

public:
	unsigned int radius;
	unsigned int awarenessRadius;
	unsigned int maxForce;
	unsigned int minForce;

	float separationDesire = 1;
	float cohesionDesire = 1;
	float aligmentDesire = 1;
	float interestDesire = 1;

	bool intersted = false;

	Vector2 PoI;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	Particle();
	Particle(unsigned int radius);
	Particle(unsigned int radius, Vector2 position);

};

