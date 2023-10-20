#pragma once

#include "raylib.h"

enum class GameSceen
{
	MENU,
	GAME,
	PAUSE,
	INSTRUCTIONS,
	CREDITS,
	EXIT,
};


namespace Globals
{
	extern const int screenWidth;
	extern const int screenHeight;
	extern bool loading;
}

namespace GameAssets
{
	extern Texture2D player;
}

namespace MenuAssets
{
	extern Texture2D background;
	extern Texture2D play;
	extern Texture2D instructions;
	extern Texture2D credits;
	extern Texture2D exit;

	extern int menuSizeX;
	extern int menuSizeY;

	extern Vector2 playPos;
	extern Vector2 instructionsPos;
	extern Vector2 creditsPos;
	extern Vector2 exitPos;
}
