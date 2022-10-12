#pragma once

#include "Settings.h"
#include "Topo.h"

struct Rock
{
	enum State
	{
		Big,
		Med,
		Small,
	};

	int maxSpeed;
	float size;
	bool active;
	float ghostCounter;
	float speed;
	float rot;
	float rotSpeed;

	State state;
	Vector2 vel;
	Vector2 pos;
	Texture2D sprite;
	Color color;
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
bool asteroidDestroyed(Asteroid& ast);
void portalAsteroids(Asteroid& ast, Settings settings);
bool checkAsteroidCollision(Asteroid& ast, Circle cir);
void checkAsteroidsCollision(Asteroid& ast1, Asteroid& ast2);
void collideRocks(Rock& rock1, Rock& rock2);
void collideBigAsteroid(Asteroid& ast);
void collideMidAsteroid(Asteroid& ast, int i);
void drawAsteroid(Asteroid ast, Settings settings);
void updateCounter(Asteroid& ast);
void updateRotation(Rock& rock);
void randomRotSpeed(float& rotSpeed);