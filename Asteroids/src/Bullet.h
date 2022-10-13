#pragma once
#include "Settings.h"
#include "Topo.h"

struct Bullet
{
	Sound shoot;
	Vector2 pos;
	Vector2 vel;
	Texture2D sprite;
	Texture2D explosion;
	int explosionFrame;
	float explosionSize;
	float speed;
	bool hit;
	bool loaded;
	float lifeSpan;
	float curLife;
	float size;
};

Bullet newBullet();
void resetBullet(Vector2 pos, Bullet& bul);
void fireBullet(Vector2 pos, Bullet& bul);
void moveBullet(Bullet& bul, Settings settings);
void drawBullet(Bullet& bul, bool showColliders);
void showExplosion(Bullet& bul);