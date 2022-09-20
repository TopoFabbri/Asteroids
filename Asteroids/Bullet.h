#pragma once
#include "Topo.h"

struct Bullet
{
	Vector2 pos;
	Vector2 vel;
	float speed;
	bool hit;
};

Bullet resetBullet(Vector2 pos, Vector2 vel);
void fireBullet(Vector2 pos, Vector2 vel, Bullet& bul);
void moveBullet(Bullet& bul);