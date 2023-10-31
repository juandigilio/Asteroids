#pragma once

#include "raylib.h"

enum class GameSceen
{
	MENU,
	GAME,
	RESULTS,
	PAUSE,
	INSTRUCTIONS,
	CREDITS,
	EXIT,
};

namespace Globals
{
	extern const int screenWidth;
	extern const int screenHeight;
	extern Vector2 screenCenter;
	extern bool loading;
	extern float interpolationFactor;
}