#pragma once

#include "Topo.h"
#include "Bullet.h"

struct Ship
{
	Vector2 pos;
	Vector2 vel;
	Color color;
	Bullet bul;
	Texture2D sprite;
	float accel;
	float speed;
	float size;
	float rot;
};

Ship newShip();
void moveShip(Ship& ship);
void updateRotation(Ship& ship);
void accelerateShip(float axisX, float axisY, Ship& ship);
void drawShip(Ship ship);
void shipPortal(Ship& ship);