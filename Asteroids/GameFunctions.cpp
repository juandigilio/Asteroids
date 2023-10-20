#include "GameFunctions.h"

#include "GameData.h"


using namespace Globals;


void InitGame(Player& player)
{
	player.texture = LoadTexture("Assets/Images/ship.png");
	player.position.x = screenWidth / 2;
	player.position.y = screenHeight / 2;
	player.speed = 0.0f;
}