#include "GameData.h"


namespace Globals
{
	extern const int screenWidth = 800;
	extern const int screenHeight = 600;
	extern bool loading = true;
}

namespace GameAssets
{
	extern Texture2D player{};
}

namespace MenuAssets
{
	extern Texture2D background{};
	extern Texture2D play{};
	extern Texture2D instructions{};
	extern Texture2D credits{};
	extern Texture2D exit{};

	extern int menuSizeX = 200;
	extern int menuSizeY = 100;

	extern Vector2 playPos{};
	extern Vector2 instructionsPos{};
	extern Vector2 creditsPos{};
	extern Vector2 exitPos{};
}