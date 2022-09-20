#include "Ship.h"

Ship newShip()
{
	Ship ship{};

	ship.pos = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	ship.vel = { 0, 0 };
	ship.color = WHITE;
	ship.bul = { resetBullet({ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }) };
	ship.sprite = LoadTexture("res/Pjship.png");
	ship.accel = 200;
	ship.speed = 1;
	ship.size = 50;
	ship.rot = 0;

	return ship;
}

void moveShip(Ship& ship)
{
	ship.pos.x += ship.vel.x * ship.speed * GetFrameTime();
	ship.pos.y += ship.vel.y * ship.speed * GetFrameTime();

	moveBullet(ship.bul);
	updateRotation(ship);

	if (ship.bul.curLife > ship.bul.lifeSpan)
		ship.bul = resetBullet(ship.pos);
}


void updateRotation(Ship& ship)
{
	
}

void accelerateShip(float axisX, float axisY, Ship& ship)
{
	ship.vel.x += axisX * ship.accel * GetFrameTime();
	ship.vel.y += axisY * ship.accel * GetFrameTime();
}

void drawShip(Ship ship)
{
	Rectangle source = { 0, 0, 98, 75 };
	Rectangle dest = { ship.pos.x - ship.size / 2, ship.pos.y - ship.size / 2, ship.size, ship.size };

	//DrawLineV({ ship.pos.x + ship.size / 2, ship.pos.y + ship.size / 2 }, GetMousePosition(), RED);
	drawBullet(ship.bul);
	//DrawCircleV(ship.pos, ship.size, WHITE);
	DrawTexturePro(ship.sprite, source, dest, { 0, 0 }, ship.rot, WHITE);
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