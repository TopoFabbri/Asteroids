#pragma once

#include "Topo.h"
#include "Ship.h"
#include "Settings.h"
#include "Menu.h"
#include "Asteroid.h"

struct Parallax
{
	Rectangle dest;
	Vector2 minPos;
	Vector2 maxPos;
	Texture2D image;
	float mult;
};

struct Game
{
	static const int maxAst = 10;
	Settings settings;
	Ship ship;
	bool isPlaying;
	Menu mainMenu;
	Menu settingsMenu;
	Menu controlsMenu;
	Menu credits;
	Menu pauseMenu;
	Texture2D bg;
	Texture2D bgStars;
	Parallax planets[2];
	Texture2D bgFog;
	Asteroid ast[maxAst];
	Color starBrightness;
	bool dimming;
	int score;
};

Game newGame();
void loop(Game& game);
void play(Game& game);
void begin(Game& game);
void update(Game& game);
void draw(Game& game);
void input(Game& game);
void checkCollisions(Game& game);
void collideShip(Asteroid& ast, Ship& ship);
bool isGameOver(Game& game);
void parallax(Game& game);
void loadTextures(Game& game);
void updateStarBrightness(Color& starBrightness, bool& dimming);
Parallax newParallax(float mult);