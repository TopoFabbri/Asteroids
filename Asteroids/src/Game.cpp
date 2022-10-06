#include "Game.h"

Texture2D space;

Game newGame()
{
	Game game;

	game.settings = newSettings();
	game.ship = newShip();
	game.planets[0] = newParallax(0.05f);
	game.planets[1] = newParallax(0.5f);
	game.isPlaying = false;
	game.mainMenu = createMenu();
	game.settingsMenu = createMenu();
	game.controlsMenu = createMenu();
	game.credits = createMenu();
	game.pauseMenu = createMenu();
	game.starBrightness = {255, 255, 255, 255};
	game.dimming = true;

	for (int i = 0; i < Game::maxAst; i++)
	{
		newAsteroid(game.ast[i]);
	}

	game.score = 0;

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

		case Scene::Pause:
			pauseMenu(game.settings, game.pauseMenu);
			break;

		default:;
		}
	}
}

void play(Game& game)
{
	// Begin
	if (!game.isPlaying)
	{
		begin(game);
	}

	// Update
	update(game);

	// Draw
	draw(game);
}

void begin(Game& game)
{
	game.isPlaying = true;
	loadTextures(game);
	game.ship = newShip();
	game.score = 0;

	for (int i = 0; i < Game::maxAst; i++)
	{
		newAsteroid(game.ast[i]);
	}
}

void update(Game& game)
{
	input(game);
	checkCollisions(game);
	moveShip(game.ship);
	shipPortal(game.ship, game.settings);
	updateStarBrightness(game.starBrightness, game.dimming);
	parallax(game);

	for (int i = 0; i < game.maxAst; i++)
	{
		moveAsteroid(game.ast[i]);
		portalAsteroids(game.ast[i], game.settings);
		updateCounter(game.ast[i]);
		if (asteroidDestroyed(game.ast[i]))
			game.ast[i].big.active = true;
	}

	if (isGameOver(game))
	{
		game.settings.scene = Scene::Credits;
		game.isPlaying = false;
	}
}

void draw(Game& game)
{
	Rectangle bgSource{ 0, 0, (float)game.bg.width, (float)game.bg.height };
	Rectangle bgDest{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

	BeginDrawing();
	ClearBackground(BLACK);
	DrawTexturePro(game.bg, bgSource, bgDest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(game.bgStars, bgSource, bgDest, { 0, 0 }, 0, game.starBrightness);
	DrawTexturePro(game.planets[0].image, bgSource, game.planets[0].dest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(game.planets[1].image, bgSource, game.planets[1].dest, { 0, 0 }, 0, WHITE);

	for (int i = 0; i < game.maxAst; i++)
	{
		drawAsteroid(game.ast[i], game.settings);
	}

	drawShip(game.ship, game.settings.showColliders);

	DrawTexturePro(game.bgFog, bgSource, bgDest, { 0, 0 }, 0, WHITE);

	DrawText(TextFormat("%i", game.score), GetScreenWidth() - MeasureText(TextFormat("%i", game.score) - 5, 30),
		5, 30, YELLOW);

	if (game.settings.drawFps)
		DrawFPS(10, 10);

	EndDrawing();
}

void input(Game& game)
{
	float axisX = 0;
	float axisY = 0;

	shipAnimator(game.ship);

	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		Vector2 moveDir = GetMousePosition();
		moveDir.x -= game.ship.pos.x;
		moveDir.y -= game.ship.pos.y;

		moveDir = normalizeVector(moveDir);

		axisX = moveDir.x;
		axisY = moveDir.y;
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		game.ship.bulletCount = 0;

		for (int i = 0; i < game.ship.maxBullets; i++)
		{
			game.ship.bulletCount = i;

			if (game.ship.bul[game.ship.bulletCount].loaded)
				break;
		}

		if (game.ship.bul[game.ship.bulletCount].loaded)
		{
			fireBullet(game.ship.pos, game.ship.bul[game.ship.bulletCount]);

			Vector2 fireDir = GetMousePosition();
			fireDir.x -= game.ship.pos.x;
			fireDir.y -= game.ship.pos.y;

			fireDir = normalizeVector(fireDir);

			if (abs(game.ship.vel.x - fireDir.x * game.ship.recoil) <= game.ship.maxSpeed)
				game.ship.vel.x -= fireDir.x * game.ship.recoil;

			if (abs(game.ship.vel.y - fireDir.y * game.ship.recoil) <= game.ship.maxSpeed)
				game.ship.vel.y -= fireDir.y * game.ship.recoil;
		}
	}

	if (IsKeyPressed(KEY_ESCAPE))
		game.settings.scene = Scene::Pause;

	accelerateShip(axisX, axisY, game.ship);
}

void checkCollisions(Game& game)
{
	for (int i = 0; i < game.maxAst; i++)
	{
		if (checkAsteroidCollision(game.ast[i], { game.ship.pos, game.ship.size }))
			collideShip(game.ast[i], game.ship);

		for (int j = i; j < game.maxAst; j++)
		{
			if (i == j)
				continue;

			checkAsteroidsCollision(game.ast[i], game.ast[j]);
		}

		for (int j = 0; j < game.ship.maxBullets; j++)
		{
			if (!game.ship.bul[j].loaded)
			{
				if (checkAsteroidCollision(game.ast[i], { game.ship.bul[j].pos, game.ship.bul[j].size }))
				{
					game.ship.bul[j].hit = true;
					game.ship.bul[j].vel = { 0, 0 };
					game.score += 10;
				}
			}
		}
	}
}

void collideShip(Asteroid& ast, Ship& ship)
{
	Vector2 colPos{};

	ship.lives--;

	if (ast.big.active && circlesCollide({ ast.big.pos, ast.big.size }, { ship.pos, ship.size }))
		colPos = getCirclesCollisionPos({ ast.big.pos, ast.big.size }, { ship.pos, ship.size });

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active && circlesCollide({ ast.med[i].pos, ast.med[i].size }, { ship.pos, ship.size }))
			colPos = getCirclesCollisionPos({ ast.med[i].pos, ast.med[i].size }, { ship.pos, ship.size });

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active && circlesCollide({ ast.small[i][j].pos, ast.small[i][j].size }, { ship.pos, ship.size }))
				colPos = getCirclesCollisionPos({ ast.small[i][j].pos, ast.small[i][j].size }, { ship.pos, ship.size });
		}
	}

	float rock1Speed = ast.big.speed;

	Vector2 newVel = normalizeVector({ ship.pos.x - colPos.x, ship.pos.y - colPos.y });
	ship.vel.x = newVel.x;
	ship.vel.y = newVel.y;
	setVectorLength(ship.vel, rock1Speed / ship.speed);
}

bool isGameOver(Game& game)
{
	if (game.ship.lives <= 0)
		return true;

	return false;
}

void parallax(Game& game)
{
	for (int i = 0; i < 2; i++)
	{
		Vector2 newPos = { game.planets[i].dest.x, game.planets[i].dest.y };

		newPos.x -= game.ship.vel.x * GetFrameTime() * game.planets[i].mult;
		newPos.y -= game.ship.vel.y * GetFrameTime() * game.planets[i].mult;

		if (inRange(newPos.x, game.planets[i].minPos.x, game.planets[i].maxPos.x))
			game.planets[i].dest.x = newPos.x;

		if (inRange(newPos.y, game.planets[i].minPos.y, game.planets[i].maxPos.y))
			game.planets[i].dest.y = newPos.y;
	}
}

void loadTextures(Game& game)
{
	game.bg = LoadTexture("res/bgs/background1.png");
	game.bgStars = LoadTexture("res/bgs/background2Stars.png");
	game.planets[0].image = LoadTexture("res/bgs/background3PlanetLeft.png");
	game.planets[1].image = LoadTexture("res/bgs/background3PlanetRight.png");
	game.bgFog = LoadTexture("res/bgs/background4Fog.png");
}

void updateStarBrightness(Color& starBrightness, bool& dimming)
{
	const float minBrigtness = 0;
	const float maxBrigtness = 255;
	float newBrightness = starBrightness.a;

	if (dimming)
		newBrightness -= 254 * GetFrameTime();
	else
		newBrightness += 254 * GetFrameTime();

	if (newBrightness <= minBrigtness)
	{
		dimming = false;
	}
	else if (newBrightness >= maxBrigtness)
	{
		dimming = true;
		newBrightness = 254;
	}

	starBrightness.r = (unsigned char)(newBrightness * 0.8);
	starBrightness.g = (unsigned char)newBrightness;
	starBrightness.b = (unsigned char)0;
	starBrightness.a = (unsigned char)newBrightness;
}

Parallax newParallax(float mult)
{
	Parallax par{};

	par.dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight(), };
	par.minPos = { -100, -100 };
	par.maxPos = { 100, 100 };
	par.mult = mult;

	return par;
}