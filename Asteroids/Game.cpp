#include "Game.h"

Game newGame()
{
	return
	{
			Scenes::Menu
	};
}

void loop(Game game)
{
	while (game.scene != Scenes::Exit)
	{
		switch (game.scene)
		{
		case Scenes::Exit: 
			
			break;

		case Scenes::Menu: 

			break;

		case Scenes::Game: 
			play(game);
			break;

		default: ;
		}
	}
}

void play(Game game)
{
}