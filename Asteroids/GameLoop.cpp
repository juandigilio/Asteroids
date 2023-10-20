#include "GameLoop.h"

#include "raymath.h"
//#include <cmath>

#include "GameFunctions.h"
#include "GameData.h"

using namespace Globals;

static void GetInput(Player& player)
{
	player.rotation = (atan2(static_cast<double>(GetMousePosition().y) - player.position.y, static_cast<double>(GetMousePosition().x) - player.position.x)) * RAD2DEG + 90;

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
 
        Vector2 direction = Vector2Subtract(GetMousePosition(), player.position);

        float length = Vector2Length(direction);

        if (length > 5)
        {
            direction = Vector2Divide(direction,  { length, length });
        }

        player.velocity = Vector2Scale(direction, player.speed);

        player.isMoving = true;
    }
    else
    {
        player.isMoving = false;
    }

    if (player.isMoving)
    {
        player.position = Vector2Add(player.position, player.velocity);
    }
}

static void Draw(Player player)
{
	DrawTexturePro(player.texture, {0, 0, 221, 264}, {player.position.x, player.position.y, 221, 264}, {110, 132}, player.rotation, WHITE);
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