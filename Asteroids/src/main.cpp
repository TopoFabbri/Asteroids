#include <iostream>
#include <ctime>

#include "Game.h"

extern Texture2D asteroidBig;
extern Texture2D asteroidMed;
extern Texture2D asteroidSmall;
extern Texture2D laser;
extern Texture2D shipNone;
extern Texture2D shipFire;
extern Texture2D shipMove;
extern Texture2D shipBoth;
extern Texture2D space;

void runProgram();
void defaults();
void loadTextures();
void unloadTextures();

void main()
{
    runProgram();
}

void runProgram()
{
    defaults();
    loadTextures();
    Game game = newGame();
    loop(game);
    unloadTextures();
}

void defaults()
{
    srand(time(nullptr));
    InitWindow(1024, 768, "Asteroids - Topo");
    HideCursor();
    SetExitKey(NULL);
    InitAudioDevice();
    SetTargetFPS(60);

    ClearBackground(BLACK);
}

void loadTextures()
{
    asteroidBig = LoadTexture("res/AsteroidBig.png");
    asteroidMed = LoadTexture("res/AsteroidMed.png");
    asteroidSmall = LoadTexture("res/AsteroidSmall.png");
    laser = LoadTexture("res/laser.png");
    shipNone = LoadTexture("res/Ship.png");
    shipFire = LoadTexture("res/ShipFire.png");
    shipMove = LoadTexture("res/ShipMove.png");
    shipBoth = LoadTexture("res/ShipBoth.png");
    space = LoadTexture("res/Space.png");
}

void unloadTextures()
{
    UnloadTexture(asteroidBig);
    UnloadTexture(asteroidMed);
    UnloadTexture(asteroidSmall);
    UnloadTexture(laser);
    UnloadTexture(shipNone);
    UnloadTexture(shipFire);
    UnloadTexture(shipMove);
    UnloadTexture(shipBoth);
    UnloadTexture(space);
}