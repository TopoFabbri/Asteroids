#include "Bullet.h"

Bullet resetBullet(Vector2 pos)
{
	Bullet bul{};

	bul.pos = pos;
	bul.vel = { 0, 0 };
	bul.speed = 500;
	bul.hit = false;
	bul.lifeSpan = 2;
	bul.curLife = bul.lifeSpan;

	return bul;
}

void fireBullet(Vector2 pos, Bullet& bul)
{
	Vector2 vel = normalizeVector({ (float)GetMouseX() - pos.x, (float)GetMouseY() - pos.y });
	bul = { pos, vel, bul.speed, false, bul.lifeSpan, 0 };
}

void moveBullet(Bullet& bul)
{
	bul.pos.x += bul.vel.x * GetFrameTime() * bul.speed;
	bul.pos.y += bul.vel.y * GetFrameTime() * bul.speed;

	bul.curLife += GetFrameTime();

	if ((int)bul.pos.x > GetScreenWidth())
		bul.pos.x = 0;
	else if ((int)bul.pos.x < 0)
		bul.pos.x = (float)GetScreenWidth();
	else if ((int)bul.pos.y > GetScreenHeight())
		bul.pos.y = 0;
	else if ((int)bul.pos.y < 0)
		bul.pos.y = (float)GetScreenHeight();
}

void drawBullet(Bullet bul)
{
	DrawCircleV(bul.pos, 3, RED);
}