#pragma once

#include "raylib.h"

enum GameSceen
{
	MENU,
	GAME,
	INSTRUCTIONS,
	CREDITS,
	EXIT,
};


namespace Globals
{
	extern const int screenWidth;
	extern const int screenHeight;
}

namespace GameAssets
{
	Texture2D player;
}

namespace MenuAssets
{
	Texture2D background;
	Texture2D play;
	Texture2D instructions;
	Texture2D credits;
	Texture2D exit;

	Vector2 playPos;
	Vector2 instructionsPos;
	Vector2 creditsPos;
	Vector2 exitPos;
}
