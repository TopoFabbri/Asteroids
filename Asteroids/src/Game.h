#pragma once

#include "Topo.h"
#include "Ship.h"
#include "Settings.h"
#include "Menu.h"
#include "Asteroid.h"

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
	Texture2D bg;
	Asteroid ast[maxAst];
};

Game newGame();
void loop(Game& game);
void play(Game& game);
void begin(Game& game);
void update(Game& game);
void draw(Game& game);
void input(Game& game);
void checkCollisions(Game& game);