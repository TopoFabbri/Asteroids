#include "Ship.h"

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

	ship.sprite = LoadTexture("res/Pjship.png");
	ship.accel = 200;
	ship.speed = 1;
	ship.size = 25;
	ship.rot = 0;
	ship.maxSpeed = 1000;

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

void updateRotation(Ship& ship)
{
	ship.rot = getRotation({ (float)GetMouseX() - ship.pos.x, (float)GetMouseY() - ship.pos.y });
}

void accelerateShip(float axisX, float axisY, Ship& ship)
{
	Vector2 newVel = ship.vel;

	newVel.x += axisX * ship.accel * GetFrameTime();
	newVel.y += axisY * ship.accel * GetFrameTime();

	if (getVectorMagnitude(newVel) >= ship.maxSpeed)
		return;
	else
		ship.vel = newVel;
}

void drawShip(Ship ship)
{
	Rectangle source = { 0, 0, 98, 75 };
	Rectangle dest = { ship.pos.x - ship.size / 2, ship.pos.y - ship.size / 2, ship.size * 2, ship.size * 2 };

	//DrawLineV({ ship.pos.x + ship.size / 2, ship.pos.y + ship.size / 2 }, GetMousePosition(), RED);

	for (int i = 0; i < ship.maxBullets; i++)
	{
		drawBullet(ship.bul[i]);
	}

	DrawTexturePro(ship.sprite, source, dest, { dest.width / 2, dest.height / 2 }, ship.rot, WHITE);
}

void shipPortal(Ship& ship)
{
	if (ship.pos.x <= 0)
		ship.pos.x = (float)GetScreenWidth();
	else if (ship.pos.x >= (float)GetScreenWidth())
		ship.pos.x = 0;

	if (ship.pos.y <= 0)
		ship.pos.y = (float)GetScreenHeight();
	else if (ship.pos.y >= (float)GetScreenHeight())
		ship.pos.y = 0;
}