#pragma once

#include "raylib.h"

namespace Assets
{
	extern Texture2D background;
	extern Texture2D play;
	extern Texture2D instructions;
	extern Texture2D credits;
	extern Texture2D exit;

	extern Font font;

	extern int menuSizeX;
	extern int menuSizeY;

	extern Vector2 playPos;
	extern Vector2 instructionsPos;
	extern Vector2 creditsPos;
	extern Vector2 exitPos;
}

void StartUp();
