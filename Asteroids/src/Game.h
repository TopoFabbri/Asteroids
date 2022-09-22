#pragma once

#include "Topo.h"
#include "Ship.h"
#include "Settings.h"
#include "Menu.h"

struct Game
{
	Settings settings;
	Ship ship;
	bool isPlaying;
	Menu mainMenu;
	Menu settingsMenu;
	Menu controlsMenu;
	Menu credits;
};

Game newGame();
void loop(Game& game);
void play(Game& game);
void begin(Game& game);
void update(Game& game);
void draw(Game& game);
void input(Game& game);