#pragma once

#include "Topo.h"
#include "Bullet.h"

struct Ship
{
	static const int maxBullets = 5;

	Vector2 pos;
	Vector2 vel;
	Color color;
	Bullet bul[maxBullets];
	Texture2D sprite;
	int bulletCount;
	float accel;
	float speed;
	float size;
	float rot;
	float maxSpeed;
};

Ship newShip();
void moveShip(Ship& ship);
void accelerateShip(float axisX, float axisY, Ship& ship);
void updateRotation(Ship& ship);
void drawShip(Ship ship);
void shipPortal(Ship& ship);