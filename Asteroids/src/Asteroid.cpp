#include "Asteroid.h"

void newRock(Rock& rock, Rock::State state)
{
	switch (state)
	{
	case Rock::Big:
		rock.size = 40;
		rock.active = true;
		rock.sprite = LoadTexture("res/AsteroidBig.png");
		break;

	case Rock::Med:
		rock.size = 20;
		rock.active = false;
		rock.sprite = LoadTexture("res/AsteroidMed.png");
		break;

	case Rock::Small:
		rock.size = 10;
		rock.active = false;
		rock.sprite = LoadTexture("res/AsteroidSmall.png");
		break;

	default:;
	}

	rock.ghostCounter = 0;
	rock.state = state;
	rock.vel = { (float)(rand() % (int)(GetScreenWidth())), (float)(rand() % (int)(GetScreenHeight())) };
	setVectorLength(rock.vel, (float)(rand() % rock.maxSpeed));
	rock.pos = { (float)(rand() % (int)(GetScreenWidth())), (float)(rand() % (int)(GetScreenHeight())) };
}

void newAsteroid(Asteroid& ast)
{
	Rock::State state = Rock::Big;

	newRock(ast.big, Rock::Big);

	for (int i = 0; i < 2; i++)
	{
		newRock(ast.med[i], Rock::Med);

		for (int j = 0; j < 2; j++)
		{
			newRock(ast.small[i][j], Rock::Small);
		}
	}
}

void moveAsteroid(Asteroid& ast)
{
	if (ast.big.active)
	{
		ast.big.pos.x += ast.big.vel.x * GetFrameTime();
		ast.big.pos.y += ast.big.vel.y * GetFrameTime();
	}

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active)
		{
			ast.med[i].pos.x += ast.med[i].vel.x * GetFrameTime();
			ast.med[i].pos.y += ast.med[i].vel.y * GetFrameTime();
		}

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active)
			{
				ast.small[i][j].pos.x += ast.small[i][j].vel.x * GetFrameTime();
				ast.small[i][j].pos.y += ast.small[i][j].vel.y * GetFrameTime();
			}
		}
	}
}

void portalAsteroids(Asteroid& ast)
{
	if (ast.big.pos.x <= 0)
	{
		ast.big.pos.x = (float)GetScreenWidth();
	}
	else if (ast.big.pos.x >= (float)GetScreenWidth())
	{
		ast.big.pos.x = 0;
	}

	if (ast.big.pos.y <= 0)
	{
		ast.big.pos.y = (float)GetScreenHeight();
	}
	else if (ast.big.pos.y >= (float)GetScreenHeight())
	{
		ast.big.pos.y = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].pos.x <= 0)
		{
			ast.med[i].pos.x = (float)GetScreenWidth();
		}
		else if (ast.med[i].pos.x >= (float)GetScreenWidth())
		{
			ast.med[i].pos.x = 0;
		}

		if (ast.med[i].pos.y <= 0)
		{
			ast.med[i].pos.y = (float)GetScreenHeight();
		}
		else if (ast.med[i].pos.y >= (float)GetScreenHeight())
		{
			ast.med[i].pos.y = 0;
		}

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active)
			{
				if (ast.small[i][j].pos.x <= 0)
				{
					ast.small[i][j].pos.x = (float)GetScreenWidth();
				}
				else if (ast.small[i][j].pos.x >= (float)GetScreenWidth())
				{
					ast.small[i][j].pos.x = 0;
				}

				if (ast.small[i][j].pos.y <= 0)
				{
					ast.small[i][j].pos.y = (float)GetScreenHeight();
				}
				else if (ast.small[i][j].pos.y >= (float)GetScreenHeight())
				{
					ast.small[i][j].pos.y = 0;
				}
			}
		}
	}
}

bool checkAsteroidCollision(Asteroid& ast, Circle cir)
{
	bool collided = false;

	if (ast.big.active)
	{
		if (circlesCollide({ ast.big.pos, ast.big.size }, cir))
		{
			collideBigAsteroid(ast);
			collided = true;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active && ast.med[i].ghostCounter <= 0)
		{
			if (circlesCollide({ ast.med[i].pos, ast.med[i].size }, cir))
			{
				collideMidAsteroid(ast, i);
				collided = true;
			}
		}

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active && ast.small[i][j].ghostCounter <= 0)
			{
				if (circlesCollide({ ast.small[i][j].pos, ast.small[i][j].size }, cir))
				{
					ast.small[i][j].active = false;
					collided = true;
				}
			}
		}
	}

	return collided;
}

void collideBigAsteroid(Asteroid& ast)
{
	ast.big.active = false;

	ast.med[0].active = true;
	ast.med[1].active = true;

	ast.med[0].ghostCounter = 1;
	ast.med[1].ghostCounter = 1;

	ast.med[0].pos = ast.big.pos;
	ast.med[1].pos = ast.big.pos;
}

void collideMidAsteroid(Asteroid& ast, int i)
{
	ast.med[i].active = false;

	ast.small[i][0].active = true;
	ast.small[i][1].active = true;

	ast.small[i][0].ghostCounter = 1;
	ast.small[i][1].ghostCounter = 1;

	ast.small[i][0].pos = ast.med[i].pos;
	ast.small[i][1].pos = ast.med[i].pos;
}

void drawAsteroid(Asteroid ast)
{
	if (ast.big.active)
		DrawTexture(ast.big.sprite, (int)(ast.big.pos.x - ast.big.size), (int)(ast.big.pos.y - ast.big.size), WHITE);
//		DrawCircleV(ast.big.pos, ast.big.size, RED);

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active)
			DrawTexture(ast.med[i].sprite, (int)(ast.med[i].pos.x - ast.med[i].size), (int)(ast.med[i].pos.y - ast.med[i].size), WHITE);
//			DrawCircleV(ast.med[i].pos, ast.med[i].size, ORANGE);

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active)
				DrawTexture(ast.small[i][j].sprite, (int)(ast.small[i][j].pos.x - ast.small[i][j].size), (int)(ast.small[i][j].pos.y - ast.small[i][j].size), WHITE);
//			DrawCircleV(ast.small[i][j].pos, ast.small[i][j].size, YELLOW);
		}
	}
}

void updateCounter(Asteroid& ast)
{
	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active && ast.med[i].ghostCounter > 0)
		{
			ast.med[i].ghostCounter -= GetFrameTime();
			ast.med[i].ghostCounter -= GetFrameTime();
		}

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active && ast.small[i][j].ghostCounter > 0)
			{
				ast.small[i][j].ghostCounter -= GetFrameTime();
				ast.small[i][j].ghostCounter -= GetFrameTime();
			}
		}
	}
}