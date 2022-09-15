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
	shipBounce(game.ship);
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

	if (IsKeyDown(KEY_W))
		axisY = -1;

	if (IsKeyDown(KEY_S))
		axisY = 1;

	if (IsKeyDown(KEY_A))
		axisX = -1;

	if (IsKeyDown(KEY_D))
		axisX = 1;

	accelerateShip(axisX, axisY, game.ship);
}