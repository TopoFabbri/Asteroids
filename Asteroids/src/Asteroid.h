#pragma once

#include "Topo.h"

struct Rock
{
	enum State
	{
		Big,
		Med,
		Small,
	};

	const int maxSpeed = 200;

	float size;
	bool active;
	float ghostCounter;

	State state;
	Vector2 vel;
	Vector2 pos;
	Texture2D sprite;
};

struct Asteroid
{
	Rock big;
	Rock med[2];
	Rock small[2][2];
};

void newRock(Rock& rock, Rock::State state);
void newAsteroid(Asteroid& ast);
void moveAsteroid(Asteroid& ast);
void portalAsteroids(Asteroid& ast);
bool checkAsteroidCollision(Asteroid& ast, Circle cir);
void collideBigAsteroid(Asteroid& ast);
void collideMidAsteroid(Asteroid& ast, int i);
void drawAsteroid(Asteroid ast);
void updateCounter(Asteroid& ast);