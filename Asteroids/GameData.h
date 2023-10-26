#pragma once

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