#pragma once

#include "topo.h"

enum class Scenes
{
	Exit,
	Menu,
	Game
};

struct Game
{
	Scenes scene;
};

Game newGame();
void loop(Game game);
void play(Game game);