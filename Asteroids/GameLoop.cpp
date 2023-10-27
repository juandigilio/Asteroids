#include "GameLoop.h"

#include "AsteroidsManager.h"

#include "raymath.h"

void CheckPlayerAsteroid(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	float actualDistance;
	float minDistance = player.radius + asteroids[0].radius;
	
	for (int i = 0; i < asteroidsQnty; i++)
	{
		if (asteroids[i].isAlive)
		{
			actualDistance = Vector2Distance(player.GetCenter(), asteroids[i].GetCenter());

			if (actualDistance <= minDistance)
			{
				player.isColliding = true;
				player.lastCollide = GetTime();
				std::cout << "Chocan" << std::endl;
			}
		}		
	}
}

void CheckCollisions(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	CheckPlayerAsteroid(player, asteroids, halfAsteroids, quarterAsteroids);
}

static void UpdateAll(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	Update(asteroids, halfAsteroids, quarterAsteroids, player);
	Update(player);

	CheckCollisions(player, asteroids, halfAsteroids, quarterAsteroids);
}

static void RestartAllEntities(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	player.position.x = screenCenter.x - (player.texture.width / 2);
	player.position.y = screenCenter.y - (player.texture.height / 2);

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