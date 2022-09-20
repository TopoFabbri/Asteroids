#include "Ship.h"

Ship newShip()
{
	return
	{
		{ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 },
		{0, 0},
		WHITE,
		200,
		1,
		15,
		0
	};
}

void moveShip(Ship& ship)
{
	ship.pos.x += ship.vel.x * ship.speed * GetFrameTime();
	ship.pos.y += ship.vel.y * ship.speed * GetFrameTime();
}

void accelerateShip(float axisX, float axisY, Ship& ship)
{
	ship.vel.x += axisX * ship.accel * GetFrameTime();
	ship.vel.y += axisY * ship.accel * GetFrameTime();
}

void drawShip(Ship ship)
{
	//DrawLineV({ ship.pos.x + ship.size / 2, ship.pos.y + ship.size / 2 }, GetMousePosition(), RED);
	DrawCircleV(ship.pos, ship.size, WHITE);
}

void shipBounce(Ship& ship)
{
	if (ship.pos.x - ship.size <= 0)
		ship.vel.x = abs(ship.vel.x);
	else if (ship.pos.x + ship.size >= (float)GetScreenWidth())
		ship.vel.x = -abs(ship.vel.x);

	if (ship.pos.y - ship.size <= 0)
		ship.vel.y = abs(ship.vel.y);
	else if (ship.pos.y + ship.size >= (float)GetScreenHeight())
		ship.vel.y = -abs(ship.vel.y);
}