#pragma once

#include "Topo.h"
#include "Bullet.h"
#include "Settings.h"

struct Ship
{
	static const int maxBullets = 50;

	Vector2 pos;
	Vector2 vel;
	Color color;
	Bullet bul[maxBullets];
	Texture2D spriteNone;
	Texture2D spriteFire;
	Texture2D spriteMove;
	Texture2D spriteBoth;
	Texture2D sprite;
	int bulletCount;
	float accel;
	float speed;
	float size;
	float rot;
	float maxSpeed;
	int lives;
	float recoil;
};

Ship newShip();
void moveShip(Ship& ship);
void accelerateShip(float axisX, float axisY, Ship& ship);
void updateRotation(Ship& ship);
void drawShip(Ship& ship, bool showColliders);
void shipPortal(Ship& ship, Settings settings);
void shipAnimator(Ship& ship);
void drawShipLives(Ship& ship);