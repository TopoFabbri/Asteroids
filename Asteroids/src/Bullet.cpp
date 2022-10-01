#include "Bullet.h"

Texture2D laser;

Bullet newBullet()
{
	Bullet bul{};

	bul.pos = {0, 0};
	bul.vel = { 0, 0 };
	bul.sprite = laser;
	bul.speed = 500;
	bul.hit = false;
	bul.loaded = true;
	bul.lifeSpan = 2;
	bul.curLife = bul.lifeSpan;
	bul.size = 7;

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

void drawBullet(Bullet bul, bool showColliders)
{
	const Vector2 size = { (float)bul.sprite.width, (float)bul.sprite.height };
	float textureAspect = size.x / size.y;
	Rectangle source = { size.x / 6 + 5 * size.x / 6, 0, size.x / 6, size.y };
	Rectangle dest = { bul.pos.x, bul.pos.y, bul.size * 2, bul.size * 2 * textureAspect };

	float rot = getRotation(bul.vel);

	DrawTexturePro(bul.sprite, source, dest, { dest.width / 2, dest.height / 2 }, rot, WHITE);

	if (showColliders)
		DrawCircleLines((int)bul.pos.x, (int)bul.pos.y, bul.size, RED);
}