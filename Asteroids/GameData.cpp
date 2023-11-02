#include "GameData.h"


namespace Globals
{
	extern const int screenWidth = 1024;
	extern const int screenHeight = 768;
	extern Vector2 screenCenter = { screenWidth / 2, screenHeight / 2};
	extern bool loading = true;
	extern float interpolationFactor = 2.0f;
	extern int highScore = 0;

	extern Music menuMusic{};
	extern Music gameLoopMusic{};

	extern Font font{};
	extern float fontSize{};
	extern float spacing = 8.0f;
	extern float instrucrtionsSpacing = 2.0f;
}