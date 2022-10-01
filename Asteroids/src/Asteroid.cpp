#include "Asteroid.h"

Texture2D asteroidBig;
Texture2D asteroidMed;
Texture2D asteroidSmall;

void newRock(Rock& rock, Rock::State state)
{
	switch (state)
	{
	case Rock::Big:
		rock.size = 40;
		rock.active = true;
		rock.sprite = asteroidBig;
		break;

	case Rock::Med:
		rock.size = 20;
		rock.active = false;
		rock.sprite = asteroidMed;
		break;

	case Rock::Small:
		rock.size = 10;
		rock.active = false;
		rock.sprite = asteroidSmall;
		break;

	default:;
	}

	rock.ghostCounter = 0;
	rock.state = state;
	rock.vel = { (float)(rand() % (int)(GetScreenWidth())), (float)(rand() % (int)(GetScreenHeight())) };
	rock.vel = normalizeVector(rock.vel);
	rock.speed = (float)(rand() % rock.maxSpeed);
	rock.pos = { (float)(rand() % (int)(GetScreenWidth())), (float)(rand() % (int)(GetScreenHeight())) };
	rock.rot = (float)(rand() % 360);
	randomRotSpeed(rock.rotSpeed);
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
		ast.big.pos.x += ast.big.vel.x * GetFrameTime() * ast.big.speed;
		ast.big.pos.y += ast.big.vel.y * GetFrameTime() * ast.big.speed;

		updateRotation(ast.big);
	}

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active)
		{
			ast.med[i].pos.x += ast.med[i].vel.x * GetFrameTime() * ast.med[i].speed;
			ast.med[i].pos.y += ast.med[i].vel.y * GetFrameTime() * ast.med[i].speed;

			updateRotation(ast.med[i]);
		}

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active)
			{
				ast.small[i][j].pos.x += ast.small[i][j].vel.x * GetFrameTime() * ast.small[i][j].speed;
				ast.small[i][j].pos.y += ast.small[i][j].vel.y * GetFrameTime() * ast.small[i][j].speed;

				updateRotation(ast.small[i][j]);
			}
		}
	}
}

bool asteroidDestroyed(Asteroid& ast)
{
	bool destroyed = true;

	if (ast.big.active)
		destroyed = false;

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active)
			destroyed = false;

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active)
				destroyed = false;
		}
	}

	return destroyed;
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

void checkAsteroidsCollision(Asteroid& ast1, Asteroid& ast2)
{
	if (ast1.big.active)
	{
		if (ast2.big.active)
		{
			if (circlesCollide({ ast1.big.pos, ast1.big.size }, { ast2.big.pos, ast2.big.size }))
				collideRocks(ast1.big, ast2.big);
		}
	}

	if (ast1.med[0].active && ast1.med[1].active)
	{
		if (circlesCollide({ ast1.med[0].pos, ast1.med[0].size }, { ast1.med[1].pos, ast1.med[1].size }))
			collideRocks(ast1.med[0], ast1.med[1]);
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (ast1.med[i].active && ast2.med[j].active)
			{
				if (circlesCollide({ ast1.med[i].pos, ast1.med[i].size }, { ast2.med[j].pos, ast2.med[j].size }))
					collideRocks(ast1.med[i], ast2.med[j]);
			}
		}

		if (ast1.med[i].active)
		{
			if (circlesCollide({ ast1.med[i].pos, ast1.med[i].size }, { ast2.med[i].pos, ast2.med[i].size }))
				collideRocks(ast1.med[i], ast2.med[i]);
		}

		for (int j = 0; j < 2; j++)
		{
			if (ast1.small[i][j].active)
			{
				if (circlesCollide({ ast1.small[i][j].pos, ast1.small[i][j].size }, { ast2.small[i][j].pos, ast2.small[i][j].size }))
					collideRocks(ast1.small[i][j], ast2.small[i][j]);
			}
		}
	}
}

void collideRocks(Rock& rock1, Rock& rock2)
{
	const Vector2 colPos = getCirclesCollisionPos({ rock1.pos, rock1.size }, { rock2.pos, rock2.size });

	float rock1Speed = rock1.speed;

	Vector2 newVel = normalizeVector({ rock1.pos.x - colPos.x, rock1.pos.y - colPos.y });

	rock1.speed = rock2.speed;
	rock1.vel.x += newVel.x;
	rock1.vel.y += newVel.y;
	rock1.vel = normalizeVector(rock1.vel);

	newVel = { rock2.pos.x - colPos.x, rock2.pos.y - colPos.y };
	rock2.speed = rock1Speed;
	rock2.vel.x += newVel.x;
	rock2.vel.y += newVel.y;
	rock2.vel = normalizeVector(rock2.vel);

	randomRotSpeed(rock1.rotSpeed);
	randomRotSpeed(rock2.rotSpeed);
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
	{
		DrawTexturePro(ast.big.sprite, { 0, 0, (float)ast.big.sprite.width, (float)ast.big.sprite.height },
			{ ast.big.pos.x, ast.big.pos.y, ast.big.size * 2, ast.big.size * 2 }, 
			{ ast.big.size, ast.big.size }, ast.big.rot, WHITE);
	}

	for (int i = 0; i < 2; i++)
	{
		if (ast.med[i].active)
		{
			DrawTexturePro(ast.med[i].sprite, { 0, 0, (float)ast.med[i].sprite.width, (float)ast.med[i].sprite.height },
				{ ast.med[i].pos.x, ast.med[i].pos.y, ast.med[i].size * 2, ast.med[i].size * 2 },
				{ ast.med[i].size, ast.med[i].size }, ast.med[i].rot, WHITE);
		}

		for (int j = 0; j < 2; j++)
		{
			if (ast.small[i][j].active)
			{
				DrawTexturePro(ast.small[i][j].sprite, { 0, 0, (float)ast.small[i][j].sprite.width, (float)ast.small[i][j].sprite.height },
					{ ast.small[i][j].pos.x, ast.small[i][j].pos.y, ast.small[i][j].size * 2, ast.small[i][j].size * 2 },
					{ ast.small[i][j].size, ast.small[i][j].size }, ast.small[i][j].rot, WHITE);
			}
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

void updateRotation(Rock& rock)
{
	rock.rot += rock.rotSpeed * GetFrameTime();
}

void randomRotSpeed(float& rotSpeed)
{
	rotSpeed = (float)(rand() % 360 - 180);
}