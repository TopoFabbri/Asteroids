#include "Ship.h"

Texture2D shipNone;
Texture2D shipFire;
Texture2D shipMove;
Texture2D shipBoth;

Ship newShip()
{
	Ship ship{};

	ship.pos = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	ship.vel = { 0, 0 };
	ship.color = WHITE;

	for (int i = 0; i < ship.maxBullets; i++)
	{
		ship.bul[i] = newBullet();
	}

	ship.spriteNone = shipNone;
	ship.spriteFire = shipFire;
	ship.spriteMove = shipMove;
	ship.spriteBoth = shipBoth;
	ship.sprite = ship.spriteNone;
	ship.accel = 100;
	ship.speed = 5;
	ship.size = 30;
	ship.rot = 0;
	ship.maxSpeed = 1000;
	ship.lives = 3;
	ship.recoil = 20;

	return ship;
}

void moveShip(Ship& ship)
{
	ship.pos.x += ship.vel.x * ship.speed * GetFrameTime();
	ship.pos.y += ship.vel.y * ship.speed * GetFrameTime();

	for (int i = 0; i < ship.maxBullets; i++)
	{
		moveBullet(ship.bul[i]);

		if (ship.bul[i].curLife > ship.bul[i].lifeSpan)
			resetBullet(ship.pos, ship.bul[i]);
	}

	updateRotation(ship);
}

void accelerateShip(float axisX, float axisY, Ship& ship)
{
	Vector2 newVel = ship.vel;

	newVel.x += axisX * ship.accel * GetFrameTime();
	newVel.y += axisY * ship.accel * GetFrameTime();

	if (newVel.x <= ship.maxSpeed)
		ship.vel.x = newVel.x;

	if (newVel.y <= ship.maxSpeed)
		ship.vel.y = newVel.y;
}

void updateRotation(Ship& ship)
{
	ship.rot = getRotation({ (float)GetMouseX() - ship.pos.x, (float)GetMouseY() - ship.pos.y });
}

void drawShip(Ship ship, bool showColliders)
{
	Rectangle source = { 0, 0, (float)ship.sprite.width, (float)ship.sprite.height };
	Rectangle dest = { ship.pos.x, ship.pos.y, ship.size * 2, ship.size * 2 };

	for (int i = 0; i < ship.maxBullets; i++)
	{
		drawBullet(ship.bul[i], showColliders);
	}

	DrawTexturePro(ship.sprite, source, dest, { dest.width / 2, dest.height / 2 }, ship.rot, WHITE);
	if (showColliders)
		DrawCircleLines((int)ship.pos.x, (int)ship.pos.y, ship.size, WHITE);
	drawShipLives(ship);
}

void shipPortal(Ship& ship)
{
	if (ship.pos.x <= 0)
	{
		ship.pos.x = (float)GetScreenWidth();
		ship.pos.y = (float)GetScreenHeight() - ship.pos.y;
	}
	else if (ship.pos.x >= (float)GetScreenWidth())
	{
		ship.pos.x = 0;
		ship.pos.y = (float)GetScreenHeight() - ship.pos.y;
	}

	if (ship.pos.y <= 0)
	{
		ship.pos.y = (float)GetScreenHeight();
		ship.pos.x = (float)GetScreenWidth() - ship.pos.x;
	}
	else if (ship.pos.y >= (float)GetScreenHeight())
	{
		ship.pos.y = 0;
		ship.pos.x = (float)GetScreenWidth() - ship.pos.x;
	}
}

void shipAnimator(Ship& ship)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
		ship.sprite = ship.spriteBoth;
	else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
		ship.sprite = ship.spriteMove;
	else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		ship.sprite = ship.spriteFire;
	else
		ship.sprite = ship.spriteNone;
}

void drawShipLives(Ship& ship)
{
	const int size = 60;
	Rectangle source{ 0, 0, (float)ship.spriteNone.width, (float)ship.spriteNone.height };
	Rectangle dest{ (float)GetScreenWidth() / 2 - (float)(size * ship.lives) / 2,
		(float)size / 2, size, size };

	for (int i = 0; i < ship.lives; i++)
	{
		DrawTexturePro(ship.spriteNone, source, dest, { (float)size / 2, (float)size / 2 }, 0, WHITE);
		dest.x += size;
	}

}