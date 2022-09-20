#pragma once
#include "Topo.h"

struct Bullet
{
	Vector2 pos;
	Vector2 vel;
	float speed;
	bool hit;
	float lifeSpan;
	float curLife;
};

Bullet resetBullet(Vector2 pos);
void fireBullet(Vector2 pos, Bullet& bul);
void moveBullet(Bullet& bul);
void drawBullet(Bullet bul);