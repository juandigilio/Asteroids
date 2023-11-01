#pragma once

#include "raylib.h"

namespace Assets
{
	extern Texture2D background;
	extern Texture2D smallContainer;
	extern Texture2D mediumContainer;
	extern Texture2D largeContainer;
	extern Texture2D play;
	extern Texture2D instructions;
	extern Texture2D credits;
	extern Texture2D exit;

	extern Texture2D bigWindow;
	extern Texture2D smallWindow;
	extern Texture2D backButton;
	extern Texture2D backButtonAct;

	extern Sound click;

	extern Font font;
	extern float fontSize;
	extern float spacing;

	extern int menuSizeX;
	extern int menuSizeY;

	extern Vector2 playPos;
	extern Vector2 instructionsPos;
	extern Vector2 creditsPos;
	extern Vector2 exitPos;

	extern Vector2 bigWindowPos;
	extern Vector2 smallWindowPos;
	extern Vector2 backButtonPos;
	extern Vector2 gitHubPos;
	extern Vector2 gitHubSize;
}

void StartUp();
