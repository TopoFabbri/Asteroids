#pragma once

#include "Topo.h"

struct Ship
{
	Vector2 pos;
	Vector2 vel;
	Color color;
	float accel;
	float speed;
	float size;
	float rot;
};

Ship newShip();
void moveShip(Ship& ship);
void accelerateShip(float axisX, float axisY, Ship& ship);
void drawShip(Ship ship);
void shipBounce(Ship& ship);