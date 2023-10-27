#include "GameLoop.h"

#include "AsteroidsManager.h"

#include "raymath.h"

void CheckPlayerAsteroid(Player& player, Asteroid* asteroids)
{
	float actualDistance;
	float minDistance;
	
}

void CheckCollisions(Player& player, Asteroid* asteroids)
{

}

void GameLoop(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	GetInput(player, gamseSceen);

	Update(asteroids, halfAsteroids, quarterAsteroids, player);
	Update(player);

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