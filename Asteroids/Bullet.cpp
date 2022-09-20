#include "Bullet.h"

void fireBullet(Vector2 pos, Bullet& bul)
{
	Vector2 vel = normalizeVector({ (float)GetMouseX() - pos.x, (float)GetMouseY() - pos.y });
	bul = {pos, vel, 100, false,};
}

void moveBullet(Bullet& bul)
{
	bul.pos.x += bul.vel.x * GetFrameTime() * bul.speed;
	bul.pos.y += bul.vel.y * GetFrameTime() * bul.speed;
}

Bullet resetBullet(Vector2 pos, Vector2 vel)
{
	Bullet bul{};

	bul.pos = pos;
	bul.vel = vel;
	bul.speed = 1;
	bul.hit = false;

	return bul;
}