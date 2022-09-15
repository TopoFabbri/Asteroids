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
    Game game = newGame();
    defaults();
    loop(game);
}

void defaults()
{
    srand(time(nullptr));
    InitWindow(800, 800, "Asteroids - Topo");
}