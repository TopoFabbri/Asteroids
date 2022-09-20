#include <iostream>
#include <ctime>

#include "Game.h"

void runProgram();
void defaults();

void main()
{
    runProgram();
}

void runProgram()
{
    defaults();
    Game game = newGame();
    loop(game);
}

void defaults()
{
    srand(time(nullptr));
    InitWindow(800, 800, "Asteroids - Topo");
}