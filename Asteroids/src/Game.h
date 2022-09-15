#pragma once

#include "Topo.h"
#include "Ship.h"

enum class Scenes
{
	Exit,
	Menu,
	Game
};

struct Game
{
	Scenes scene;
	Ship ship;
	bool isPlaying;
};

Game newGame();
void loop(Game& game);
void play(Game& game);
void begin(Game& game);
void update(Game& game);
void draw(Game& game);
void input(Game& game);