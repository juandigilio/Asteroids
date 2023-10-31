#include "GameLoop.h"

#include "AsteroidsManager.h"

#include "raymath.h"

using namespace AsteroidsManager;

bool CheckCollision(float radius1, float radius2, Vector2 position1, Vector2 position2)
{
	float actualDistance = Vector2Distance(position1, position2);
	float minDistance = radius1 + radius2;

	if (actualDistance <= minDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UpdateCollisions(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		if (asteroids[i].isAlive)
		{
			if (CheckCollision(player.radius, asteroids[i].radius, player.GetCenter(), asteroids[i].GetCenter()))
			{
				player.isColliding = true;
				player.lastCollide = GetTime();
				std::cout << "player crash big" << std::endl;
			}
			else
			{
				for (int j = 0; j < maxBulletsQnty; j++)
				{
					if (player.bullets[j].isAlive && CheckCollision(player.bullets[j].radius, asteroids[i].radius, player.bullets[j].GetCenter(), asteroids[i].GetCenter()))
					{
						asteroids[i].isAlive = false;
						activeAsteroids--;
						player.bullets[j].isAlive = false;
						SpawnChildrens(asteroids[i], halfAsteroids, activeHalfs, halfAsteroidsQnty);
					}
				}
			}
		}
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		if (halfAsteroids[i].isAlive)
		{
			if (CheckCollision(player.radius, halfAsteroids[i].radius, player.GetCenter(), halfAsteroids[i].GetCenter()))
			{
				player.isColliding = true;
				player.lastCollide = GetTime();
				std::cout << "player crash half" << std::endl;
			}
			else
			{
				for (int j = 0; j < maxBulletsQnty; j++)
				{
					if (player.bullets[j].isAlive && CheckCollision(player.bullets[j].radius, halfAsteroids[i].radius, player.bullets[j].GetCenter(), halfAsteroids[i].GetCenter()))
					{
						halfAsteroids[i].isAlive = false;
						activeHalfs--;
						player.bullets[j].isAlive = false;
						SpawnChildrens(halfAsteroids[i], quarterAsteroids, activeQuarters, quarterAsteroidsQnty);
					}
				}
			}
		}
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		if (quarterAsteroids[i].isAlive)
		{
			if (CheckCollision(player.radius, quarterAsteroids[i].radius, player.GetCenter(), quarterAsteroids[i].GetCenter()))
			{
				player.isColliding = true;
				player.lastCollide = GetTime();
				std::cout << "player crash quarter" << std::endl;
			}
			else
			{
				for (int j = 0; j < maxBulletsQnty; j++)
				{
					if (player.bullets[j].isAlive && CheckCollision(player.bullets[j].radius, quarterAsteroids[i].radius, player.bullets[j].GetCenter(), quarterAsteroids[i].GetCenter()))
					{
						quarterAsteroids[i].isAlive = false;
						activeQuarters--;
						player.bullets[j].isAlive = false;
					}
				}
			}
		}
	}
}

static void UpdateAll(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	Update(asteroids, halfAsteroids, quarterAsteroids, player);
	Update(player);

	UpdateCollisions(player, asteroids, halfAsteroids, quarterAsteroids);
}

static void RestartAllEntities(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	player.position.x = screenCenter.x - (player.texture.width / 2);
	player.position.y = screenCenter.y - (player.texture.height / 2);
	player.velocity = { 0, 0 };
	player.speed = 0;

	for (int i = 0; i < maxBulletsQnty; i++)
	{
		player.bullets[i].isAlive = false;
		player.bullets[i].firstCrossing = true;
	}

	for (int i = 0; i < asteroidsQnty; i++)
	{
		asteroids[i].isAlive = false;
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		halfAsteroids[i].isAlive = false;
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		quarterAsteroids[i].isAlive = false;
	}

	activeAsteroids = 0;
	activeHalfs = 0;
	activeQuarters = 0;
}

void ShowCrash(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	player.rotation += 0.6f;

	if (player.rotation >= 360.0f)
	{
		player.rotation = 0.0f;
	}

	if (GetTime() - player.lastCollide > 2.0f)
	{
		player.isColliding = false;
		player.availableLives--;

		RestartAllEntities(player, asteroids, halfAsteroids, quarterAsteroids);
	}
}

void GameLoop(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	if (!player.isColliding)
	{
		GetInput(player, gamseSceen);

		UpdateAll(player, asteroids, halfAsteroids, quarterAsteroids);
	}
	else
	{
		ShowCrash(player, asteroids, halfAsteroids, quarterAsteroids);
	}

	Draw(player);
	Draw(asteroids, asteroidsQnty);
	Draw(halfAsteroids, halfAsteroidsQnty);
	Draw(quarterAsteroids, quarterAsteroidsQnty);
}

void Play(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	if (loading)
	{
		Load(player);
		Load(asteroids, halfAsteroids, quarterAsteroids);
		loading = false;
	}
	
	GameLoop(player, asteroids, halfAsteroids, quarterAsteroids, gamseSceen);
}