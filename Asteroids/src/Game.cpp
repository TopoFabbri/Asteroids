#include "Game.h"

Game newGame()
{
	return
	{
		Scenes::Game,
		newShip(),
		false
	};
}

void loop(Game& game)
{
	while (game.scene != Scenes::Exit)
	{
		if (WindowShouldClose())
			game.scene = Scenes::Exit;

		switch (game.scene)
		{
		case Scenes::Exit:

			break;

		case Scenes::Menu:

			break;

		case Scenes::Game:
			play(game);
			break;

		default:;
		}
	}
}

void play(Game& game)
{
	begin(game);
	update(game);
	draw(game);
}

void begin(Game& game)
{
	if (!game.isPlaying)
	{
		game.isPlaying = true;
		game.ship = newShip();
	}
}

void update(Game& game)
{
	input(game);
	moveShip(game.ship);
	shipPortal(game.ship);
}

void draw(Game& game)
{
	BeginDrawing();
	ClearBackground(BLACK);

	drawShip(game.ship);

	EndDrawing();
}

void input(Game& game)
{
	float axisX = 0;
	float axisY = 0;

	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		Vector2 moveDir = { (float)GetMouseX(), (float)GetMouseY() };

		moveDir = normalizeVector({ moveDir.x - game.ship.pos.x, moveDir.y - game.ship.pos.y });

		axisX = moveDir.x;
		axisY = moveDir.y;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		fireBullet(game.ship.pos, game.ship.bul);
	}

	accelerateShip(axisX, axisY, game.ship);
}