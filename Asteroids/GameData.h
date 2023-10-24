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


