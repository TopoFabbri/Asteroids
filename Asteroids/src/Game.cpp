#include "Game.h"

Game newGame()
{
	Game game;

	game.settings = newSettings();
	game.ship = newShip();
	game.isPlaying = false;
	game.mainMenu = createMenu();
	game.settingsMenu = createMenu();
	game.controlsMenu = createMenu();
	game.credits = createMenu();
	game.bg = LoadTexture("res/Space.png");

	for (int i = 0; i < Game::maxAst; i++)
	{
		newAsteroid(game.ast[i]);
	}

	return game;
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
	// Begin
	begin(game);

	// Update
	update(game);

	// Draw
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
	checkCollisions(game);

	for (int i = 0; i < game.maxAst; i++)
	{
		moveAsteroid(game.ast[i]);
		portalAsteroids(game.ast[i]);
		updateCounter(game.ast[i]);
	}
}

void draw(Game& game)
{
	Rectangle bgSource{ 0, 0, (float)game.bg.width, (float)game.bg.height };
	Rectangle bgDest{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

	BeginDrawing();
	DrawTexturePro(game.bg, bgSource, bgDest, { 0, 0 }, 0, WHITE);

	for (int i = 0; i < game.maxAst; i++)
	{
		drawAsteroid(game.ast[i]);
	}

	drawShip(game.ship);

	if (game.settings.drawFps)
		DrawFPS(10, 10);

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

	if (IsKeyPressed(KEY_SPACE))
		game.settings.scene = Scene::MainMenu;

	accelerateShip(axisX, axisY, game.ship);
}

void checkCollisions(Game& game)
{
	for (int i = 0; i < game.maxAst; i++)
	{
		checkAsteroidCollision(game.ast[i], { game.ship.pos, game.ship.size });

		for (int j = 0; j < game.ship.maxBullets; j++)
		{
			if (!game.ship.bul[j].loaded)
			{
				if (checkAsteroidCollision(game.ast[i], { game.ship.bul[j].pos, game.ship.bul[j].size }))
					resetBullet(game.ship.pos, game.ship.bul[j]);
			}
		}
	}
}