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
    InitWindow(1920, 1080, "Asteroids - Topo");
    SetExitKey(NULL);

    ClearBackground(BLACK);
}