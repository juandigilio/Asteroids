#include "AsteroidsManager.h"

#include "GameData.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>

namespace AsteroidsManager
{
	extern int asteroidsQnty = 12;
	extern int halfAsteroidsQnty = asteroidsQnty * 3;
	extern int quarterAsteroidsQnty = halfAsteroidsQnty * 3;
	extern int activeAsteroids = 0;
	extern int activeHalfs = 0;
	extern int activeQuarters = 0;
	extern float lastDrop = 0.0f;
}


void LoadAsteroids(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		asteroids[i].texture = LoadTexture("Assets/Images/bigAsteroid.png");
		asteroids[i].radius = asteroids[i].texture.width / 2.0f;
		asteroids[i].mass = 1.0f;
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		halfAsteroids[i].texture = LoadTexture("Assets/Images/halfAsteroid.png");
		halfAsteroids[i].radius = halfAsteroids[i].texture.width / 2.0f;
		halfAsteroids[i].mass = 0.75f;
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		quarterAsteroids[i].texture = LoadTexture("Assets/Images/quarterAsteroid.png");
		quarterAsteroids[i].radius = quarterAsteroids[i].texture.width / 2.0f;
		quarterAsteroids[i].mass = 0.5f;
	}
}

static void SpawnBig(Asteroid& asteroid, Player player)
{
	float elapsedTime = static_cast<float>(GetTime()) - lastDrop;

	if (activeAsteroids < asteroidsQnty && elapsedTime > 3.0f)
	{
		int spawnPoint;
		int playerSector;

		Vector2 spawner1{ 0.0f,0.0f };
		Vector2 spawner2{ 0.0f, static_cast<float>(screenHeight) };
		Vector2 spawner3{ static_cast<float>(screenWidth),0.0f };
		Vector2 spawner4{ static_cast<float>(screenWidth),static_cast<float>(screenHeight) };

		if (player.position.x < screenWidth / 2 && player.position.y < screenHeight / 2.0f)
		{
			playerSector = 0;
		}
		else if (player.position.x > screenWidth / 2 && player.position.y < screenHeight / 2.0f)
		{
			playerSector = 1;
		}
		else if (player.position.x < screenWidth / 2 && player.position.y > screenHeight / 2.0f)
		{
			playerSector = 2;
		}
		else
		{
			playerSector = 3;
		}

		do
		{
			spawnPoint = rand() % 4;

		} while (spawnPoint == playerSector);

		switch (spawnPoint)
		{
		case 0:
		{
			asteroid.position = spawner1;
			break;
		}
		case 1:
		{
			asteroid.position = spawner2;
			break;
		}
		case 2:
		{
			asteroid.position = spawner3;
			break;
		}
		case 3:
		{
			asteroid.position = spawner4;
			break;
		}
		}

		asteroid.direction = Vector2Subtract(player.position, asteroid.position);
		float length = Vector2Length(asteroid.direction);
		asteroid.direction = Vector2Divide(asteroid.direction, { length, length });

		asteroid.isAlive = true;
		activeAsteroids++;
		lastDrop = static_cast<float>(GetTime());

		std::cout << "Active instances: " << activeAsteroids << std::endl;
	}
}

void SpawnChildrens(Bullet bullet, Asteroid& brocken, Asteroid* toSpawn, int& actives, int& maxQnty)
{
	int counter = 0;

	for (int i = 0; i < maxQnty; i++)
	{
		if (counter == 2 || actives == maxQnty)
		{
			break;
		}
		else if (!toSpawn[i].isAlive && counter == 0)
		{
			toSpawn[i].isAlive = true;
			toSpawn[i].isSpawning = true;
			toSpawn[i].lastSpawn = static_cast<float>(GetTime());
			toSpawn[i].position = brocken.position;
			toSpawn[i].direction = bullet.direction;
			toSpawn[i].direction = Vector2Rotate(toSpawn[i].direction, -90.0f);
			actives++;
			counter++;
		}
		else if (!toSpawn[i].isAlive && counter == 1)
		{
			toSpawn[i].isAlive = true;
			toSpawn[i].isSpawning = true;
			toSpawn[i].lastSpawn = static_cast<float>(GetTime());
			toSpawn[i].position = brocken.position;
			toSpawn[i].direction = bullet.direction;
			toSpawn[i].direction = Vector2Rotate(toSpawn[i].direction, 90.0f);
			actives++;
			counter++;
		}
	}
}

static void Move(Asteroid* asteroids, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		if (asteroids[i].isAlive)
		{
			asteroids[i].velocity = Vector2Scale(asteroids[i].direction, asteroids[i].speed * GetFrameTime());
			asteroids[i].position = Vector2Add(asteroids[i].position, asteroids[i].velocity);

			if (asteroids[i].position.x > screenWidth + asteroids[i].texture.width / 2.0f)
			{
				asteroids[i].position.x = (-asteroids[i].texture.width / 2.0f);
				asteroids[i].position.y = screenHeight - asteroids[i].position.y;
			}
			else if (asteroids[i].position.x < 0.0f - asteroids[i].texture.width / 2.0f)
			{
				asteroids[i].position.x = screenWidth + (asteroids[i].texture.width / 2.0f);
				asteroids[i].position.y = screenHeight - asteroids[i].position.y;
			}
			else if (asteroids[i].position.y > screenHeight + asteroids[i].texture.height / 2.0f)
			{
				asteroids[i].position.x = screenWidth - asteroids[i].position.x;
				asteroids[i].position.y = (-asteroids[i].texture.height / 2.0f);
			}
			else if (asteroids[i].position.y < 0.0f - asteroids[i].texture.height / 2.0f)
			{
				asteroids[i].position.x = screenWidth - asteroids[i].position.x;
				asteroids[i].position.y = screenHeight + (asteroids[i].texture.height / 2.0f);
			}
		}
	}
}

void DrawAsteroids(Asteroid* asteroids, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		if (asteroids[i].isAlive)
		{
			DrawTextureV(asteroids[i].texture, asteroids[i].position, RAYWHITE);
		}
	}
}

static void CheckTimers(Asteroid& asteroid)
{
	float elapsedTime;

	if (asteroid.isSpawning)
	{
		elapsedTime = static_cast<float>(GetTime()) - asteroid.lastSpawn;

		if (elapsedTime > 1.0f)
		{
			asteroid.isSpawning = false;
		}
	}
	else if (asteroid.isColliding)
	{
		elapsedTime = static_cast<float>(GetTime()) - asteroid.lastCollide;

		if (elapsedTime > 1.0f)
		{
			asteroid.isColliding = false;
		}
	}
}

void UpdateAsteroids(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, Player player)
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		if (!asteroids[i].isAlive)
		{
			SpawnBig(asteroids[i], player);
		}
		else 
		{
			CheckTimers(asteroids[i]);
		}
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		if (halfAsteroids[i].isAlive)
		{
			CheckTimers(halfAsteroids[i]);
		}
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		if (quarterAsteroids[i].isAlive)
		{
			CheckTimers(quarterAsteroids[i]);
		}
	}
	
	Move(asteroids, asteroidsQnty);
	Move(halfAsteroids, halfAsteroidsQnty);
	Move(quarterAsteroids, quarterAsteroidsQnty);
}
