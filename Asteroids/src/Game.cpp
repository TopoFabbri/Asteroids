#include "Game.h"

Game newGame()
{
	return
	{
		newSettings(),
		newShip(),
		false,
		createMenu()
	};
}

void loop(Game& game)
{
	while (game.settings.scene != Scene::Exit)
	{
		if (WindowShouldClose())
			game.settings.scene = Scene::Exit;

		switch (game.settings.scene)
		{
		case Scene::Exit:

			break;

		case Scene::MainMenu:
			mainMenu(game.settings, game.mainMenu);
			break;

		case Scene::Game:
			play(game);
			break;

		case Scene::SettingsMenu:
			settingsMenu(game.settings, game.settingsMenu);
			break;

		case Scene::ControlsMenu:
			controlsMenu(game.settings, game.controlsMenu);
			break;

		case Scene::Credits:
			creditsMenu(game.settings, game.credits);
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
		game.ship.bulletCount = 0;

		for (int i = 0; i < game.ship.maxBullets; i++)
		{
			game.ship.bulletCount = i;

			if (game.ship.bul[game.ship.bulletCount].loaded)
				break;
		}

		if (game.ship.bul[game.ship.bulletCount].loaded)
			fireBullet(game.ship.pos, game.ship.bul[game.ship.bulletCount]);
	}

	accelerateShip(axisX, axisY, game.ship);
}