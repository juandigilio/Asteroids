#include "GameLoop.h"

#include <cmath>

#include "GameFunctions.h"
#include "GameData.h"

using namespace Globals;

static void GetInput(Player& player)
{
	player.rotation = (atan2(GetMousePosition().y - player.position.y, GetMousePosition().x - player.position.x)) * RAD2DEG + 90;
}

static void Draw(Player player)
{
	DrawTextureEx(player.texture, player.position, player.rotation, 1.0, WHITE);
}

void Play(Player& player, GameSceen& gamseSceen)
{
	if (loading)
	{
		InitGame(player);

		loading = false;
	}
	
	GetInput(player);

	Draw(player);
}