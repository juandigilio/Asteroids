#include "GameLoop.h"

#include "raymath.h"


void GameLoop(Player& player, Asteroid asteroids[], GameSceen& gamseSceen)
{
	GetInput(player, gamseSceen);
	Update(asteroids, player);
	Update(player);
	Draw(player);
}

void Play(Player& player, Asteroid asteroids[], GameSceen& gamseSceen)
{
	if (loading)
	{
		Load(player);
		Load(asteroids);
		loading = false;
	}
	
	GameLoop(player, asteroids, gamseSceen);
}

