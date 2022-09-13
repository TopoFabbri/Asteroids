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
    loop();
}

void defaults()
{
    srand(time(nullptr));
}