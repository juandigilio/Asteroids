#include "GameData.h"


namespace Globals
{
	extern const int screenWidth = 800;
	extern const int screenHeight = 600;
}

namespace GameAssets
{
	Texture2D player{};
}

namespace MenuAssets
{
	Texture2D play{};
	Texture2D instructions{};
	Texture2D credits{};
	Texture2D exit{};

	Vector2 playPos{};
	Vector2 instructionsPos{};
	Vector2 creditsPos{};
	Vector2 exitPos{};
}