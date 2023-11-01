#include "MenuManager.h"

#include "GameData.h"
#include "Player.h"
#include "Asteroids.h"
#include "AsteroidsManager.h"
#include "GameLoop.h"


namespace Assets
{
	extern Texture2D background{};
	extern Texture2D smallContainer{};
	extern Texture2D mediumContainer{};
	extern Texture2D largeContainer{};
	extern Texture2D play{};
	extern Texture2D playSelect{};
	extern Texture2D instructions{};
	extern Texture2D credits{};
	extern Texture2D exit{};

	extern Texture2D bigWindow{};
	extern Texture2D smallWindow{};
	extern Texture2D backButton{};
	extern Texture2D backButtonAct{};

	extern Font font{};
	extern float fontSize{};
	extern float spacing = 8.0f;
	extern float instrucrtionsSpacing = 2.0f;

	extern int menuSizeX = 200;
	extern int menuSizeY = 100;

	extern Vector2 playPos{};
	extern Vector2 playPosContainer{};
	extern Vector2 instructionsPos{};
	extern Vector2 instructionsPosContainer{};
	extern Vector2 creditsPos{};
	extern Vector2 creditsPosContainer{};
	extern Vector2 exitPos{};
	extern Vector2 exitPosContainer{};

	extern Vector2 bigWindowPos{};
	extern Vector2 smallWindowPos{};
	extern Vector2 backButtonPos{};
	extern Vector2 gitHubPos{};
	extern Vector2 gitHubSize{};
}

using namespace Globals;
using namespace Assets;
using namespace AsteroidsManager;

void InitMenu()
{
	background = LoadTexture("Assets/Images/Menu/background.png");
	smallContainer = LoadTexture("Assets/Images/Menu/smallContainer.png");
	mediumContainer = LoadTexture("Assets/Images/Menu/mediumContainer.png");
	largeContainer = LoadTexture("Assets/Images/Menu/largeContainer.png");

	bigWindow = LoadTexture("Assets/Images/Menu/bigWindow.png");
	smallWindow = LoadTexture("Assets/Images/Menu/smallWindow.png");
	backButton = LoadTexture("Assets/Images/Menu/backBtn.png");
	backButtonAct = LoadTexture("Assets/Images/Menu/backBtnAct.png");


	font = LoadFont("Assets/Fonts/04B_30__.TTF");
	fontSize = font.baseSize * 2.0f;

	playPosContainer.x = (screenWidth / 2) - (smallContainer.width / 2);
	playPosContainer.y = ((screenHeight / 5)) - (smallContainer.height / 2);
	playPos.x = (screenWidth / 2) - MeasureTextEx(font, "Play", fontSize, spacing).x / 2.0f + 8;
	playPos.y = (screenHeight / 5) - (fontSize / 2);

	instructionsPosContainer.x = (screenWidth / 2) - (largeContainer.width / 2);
	instructionsPosContainer.y = ((screenHeight / 5) * 2) - (largeContainer.height / 2);
	instructionsPos.x = (screenWidth / 2) - MeasureTextEx(font, "Instructions", fontSize, instrucrtionsSpacing).x / 2.0f + 8;
	instructionsPos.y = ((screenHeight / 5) * 2) - (fontSize / 2);

	creditsPosContainer.x = (screenWidth / 2) - (mediumContainer.width / 2);
	creditsPosContainer.y = ((screenHeight / 5) * 3) - (mediumContainer.height / 2);
	creditsPos.x = (screenWidth / 2) - MeasureTextEx(font, "Credits", fontSize, spacing).x / 2.0f + 20;
	creditsPos.y = ((screenHeight / 5) * 3) - (fontSize / 2);

	exitPosContainer.x = (screenWidth / 2) - (smallContainer.width / 2);
	exitPosContainer.y = (screenHeight / 5) * 4 - (smallContainer.height / 2);
	exitPos.x = (screenWidth / 2) - MeasureTextEx(font, "Exit", fontSize, spacing).x / 2.0f + 8;
	exitPos.y = (screenHeight / 5) * 4 -(fontSize / 2);

	backButtonPos.x = 15;
	backButtonPos.y = 15;
}

static void GetInput(GameSceen& currentSceen)
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	if (currentSceen == GameSceen::MENU)
	{
		if ((mouseX > playPosContainer.x && mouseX < playPosContainer.x + smallContainer.width) && (mouseY > playPosContainer.y && mouseY < playPosContainer.y + smallContainer.height))
		{
			DrawTextEx(font, "Play", playPos, fontSize, spacing, ORANGE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentSceen = GameSceen::GAME;
			}
		}
		else if ((mouseX > instructionsPosContainer.x && mouseX < instructionsPosContainer.x + largeContainer.width) && (mouseY > instructionsPosContainer.y && mouseY < instructionsPosContainer.y + largeContainer.height))
		{
			DrawTextEx(font, "Instructions", instructionsPos, fontSize, instrucrtionsSpacing, ORANGE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentSceen = GameSceen::INSTRUCTIONS;
			}
		}
		else if ((mouseX > creditsPosContainer.x && mouseX < creditsPosContainer.x + mediumContainer.width) && (mouseY > creditsPosContainer.y && mouseY < creditsPosContainer.y + mediumContainer.height))
		{
			DrawTextEx(font, "Credits", creditsPos, fontSize, 3, ORANGE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentSceen = GameSceen::CREDITS;
			}
		}
		else if ((mouseX > exitPosContainer.x && mouseX < exitPosContainer.x + smallContainer.width) && (mouseY > exitPosContainer.y && mouseY < exitPosContainer.y + smallContainer.height))
		{
			DrawTextEx(font, "Exit", exitPos, fontSize, spacing, ORANGE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentSceen = GameSceen::EXIT;
			}
		}
	}
	else
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;
		}
		else if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + backButton.width) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + backButton.height))
		{
			DrawTextureV(backButtonAct, backButtonPos, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentSceen = GameSceen::MENU;
			}
		}
		else if ((mouseX > gitHubPos.x && mouseX < gitHubPos.x + gitHubSize.x) && (mouseY > gitHubPos.y && mouseY < gitHubPos.y + gitHubSize.y))
		{
			DrawTextEx(font, "https://github.com/juandigilio", gitHubPos, fontSize * 0.2f, spacing / 8.0f, GREEN);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				OpenURL("https://github.com/juandigilio");
			}
		}
	}

}

static void DrawMain()
{
	DrawTexture(background, 0, 0, WHITE);
	DrawTextureEx(smallContainer, playPosContainer, 0, 1.0, WHITE);
	DrawTextureEx(largeContainer, instructionsPosContainer, 0, 1.0, WHITE);
	DrawTextureEx(mediumContainer, creditsPosContainer, 0, 1.0, WHITE);
	DrawTextureEx(smallContainer, exitPosContainer, 0, 1.0, WHITE);

	DrawTextEx(font, "Play", playPos, fontSize, spacing, RAYWHITE);
	DrawTextEx(font, "Instructions", instructionsPos, fontSize, instrucrtionsSpacing, RAYWHITE);
	DrawTextEx(font, "Credits", creditsPos, fontSize, 3, RAYWHITE);
	DrawTextEx(font, "Exit", exitPos, fontSize, spacing, RAYWHITE);
}

void ShowMenu(GameSceen& currentSceen)
{
	DrawMain();

	GetInput(currentSceen);
}

static void DrawInstrucions()
{
	bigWindowPos.x = (screenWidth / 2) - (bigWindow.width / 2);
	bigWindowPos.y = (screenHeight / 2) - (bigWindow.height / 2);

	Vector2 textPos;

	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(bigWindow, bigWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "INSTRUCTIONS", fontSize * 0.85f, spacing / 2.0f).x / 2.0f;
	textPos.y = (screenHeight / 6) - fontSize + 10;
	DrawTextEx(font, "INSTRUCTIONS", textPos, fontSize * 0.85f, spacing / 2.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Press left click once to shoot and get pressed", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y = (screenHeight / 5) + (fontSize) - 20;
	DrawTextEx(font, "Press once left click to shoot and get pressed", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "right click to acelerate, ship will allways follow", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "right click to acelerate, ship will allways follow", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "mouse arrow. Destroy as many asteroids as possible", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "mouse arrow. Destroy as many asteroids as possible", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "and set the new record! Game will end when you", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "and set the new record! Game will end when you", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "loose all your lives, but there is not a win", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "loose all your lives, but there is not a win", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "condition, it's just a highest score comp.", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "condition, it's just a highest score comp.", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "(Press ESC to pause)", fontSize / 3.0f, spacing / 3.0f).x / 2.0f;
	textPos.y += 160;
	DrawTextEx(font, "(Press ESC to pause)", textPos, fontSize / 3.0f, spacing / 3.0f, RAYWHITE);
}

static void ShowInstructions(GameSceen& currentSceen)
{
	DrawInstrucions();

	GetInput(currentSceen);
}

static void DrawCredits(GameSceen& currentSceen)
{
	Vector2 textPos;

	smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
	smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f);

	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(smallWindow, smallWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Created by Juan Digilio", fontSize * 0.6f, spacing / 4.0f).x / 2.0f;
	textPos.y = smallWindowPos.y - 80;
	DrawTextEx(font, "Created by Juan Digilio", textPos, fontSize * 0.6f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Assets downloaded from itch.io", fontSize * 0.4f, spacing / 8.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "Assets downloaded from itch.io", textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);
	
	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "This is remake of the classic", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 75;
	DrawTextEx(font, "This is remake of the classic", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Asteroids game made in raylib for my", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "Asteroids game made in raylib for my", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "coursing at Image-Campus in my first", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "coursing at Image-Campus in my first", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "year of video games development.", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "year of video games development.", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "The code is open source and you", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "The code is open source and you", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "can find it in my GitHub", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "can find it in my GitHub", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	gitHubSize = MeasureTextEx(font, "https://github.com/juandigilio", fontSize * 0.2f, spacing / 8.0f);

	gitHubPos.x = (screenWidth / 2) - gitHubSize.x / 2.0f;
	gitHubPos.y = textPos.y + 30;
	DrawTextEx(font, "https://github.com/juandigilio", gitHubPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);
}

void ShowCredits(GameSceen& currentSceen)
{
	DrawCredits(currentSceen);

	GetInput(currentSceen);
}

void StartUp()
{
	GameSceen currentSceen = GameSceen::MENU;

	Player player;

	Asteroid* asteroids = new Asteroid[asteroidsQnty];
	Asteroid* halfAsteroids = new Asteroid[halfAsteroidsQnty];
	Asteroid* cuarterAsteroids = new Asteroid[quarterAsteroidsQnty];

	srand(time(NULL));

	InitWindow(screenWidth, screenHeight, "After-Roids");

	InitMenu();

	while (currentSceen != GameSceen::EXIT)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentSceen)
		{
			case GameSceen::MENU:
			{
				ShowMenu(currentSceen);
				break;
			}
			case GameSceen::GAME:
			{
				Play(player, asteroids, halfAsteroids, cuarterAsteroids, currentSceen);
				break;
			}
			case GameSceen::RESULTS:
			{
				
				break;
			}
			case GameSceen::PAUSE:
			{
				break;
			}
			case GameSceen::INSTRUCTIONS:
			{
				ShowInstructions(currentSceen);
				break;
			}
			case GameSceen::CREDITS:
			{
				ShowCredits(currentSceen);
				break;
			}
			case GameSceen::EXIT:
			{
				delete[] asteroids;
				delete[] halfAsteroids;
				delete[] cuarterAsteroids;

				CloseWindow();

				break;
			}
		}

		EndDrawing();
	}
}