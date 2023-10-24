#include "GameLoop.h"

#include "raymath.h"

#include "GameFunctions.h"

//using namespace Globals;

void GameLoop(Player& player, GameSceen& gamseSceen)
{
	GetInput(player, gamseSceen);
	Update(player);
	Draw(player);
}

void Play(Player& player, GameSceen& gamseSceen)
{
	if (loading)
	{
		Load(player);

		loading = false;
	}
	
	GameLoop(player, gamseSceen);
}

