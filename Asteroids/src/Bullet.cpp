#include "Bullet.h"

Bullet newBullet()
{
	Bullet bul{};

	bul.pos = {0, 0};
	bul.vel = { 0, 0 };
	bul.sprite = LoadTexture("res/laser.png");
	bul.speed = 500;
	bul.hit = false;
	bul.loaded = true;
	bul.lifeSpan = 2;
	bul.curLife = bul.lifeSpan;
	bul.size = 9;

	return bul;
}

void resetBullet(Vector2 pos, Bullet& bul)
{
	bul.pos = pos;
	bul.vel = { 0, 0 };
	bul.speed = 500;
	bul.hit = false;
	bul.loaded = true;
	bul.lifeSpan = 2;
	bul.curLife = bul.lifeSpan;
}

void fireBullet(Vector2 pos, Bullet& bul)
{
	resetBullet(pos, bul);

	Vector2 vel = normalizeVector({ (float)GetMouseX() - pos.x, (float)GetMouseY() - pos.y });

	bul.vel = vel;
	bul.hit = false;
	bul.loaded = false;
	bul.curLife = 0;
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
	const Vector2 size = { 9, 54 };
	Rectangle dest = { bul.pos.x - size.x / 2, bul.pos.y - size.y / 2, size.x, size.y };

	float rot = getRotation(bul.vel);

	DrawTexturePro(bul.sprite, { 0, 0, size.x, size.y }, dest, { size.x / 2, size.y / 2 }, rot, WHITE);
	DrawCircleLines((int)bul.pos.x, (int)bul.pos.y, bul.size, RED);
}