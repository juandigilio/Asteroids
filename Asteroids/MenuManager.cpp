#include "MenuManager.h"

#include "GameData.h"
#include "Player.h"
#include "Asteroids.h"
#include "AsteroidsManager.h"
#include "GameLoop.h"


namespace Assets
{
	extern Texture2D background{};
	extern Texture2D play{};
	extern Texture2D instructions{};
	extern Texture2D credits{};
	extern Texture2D exit{};

	extern Font font{};

	extern int menuSizeX = 200;
	extern int menuSizeY = 100;

	extern Vector2 playPos{};
	extern Vector2 instructionsPos{};
	extern Vector2 creditsPos{};
	extern Vector2 exitPos{};
}

using namespace Globals;
using namespace Assets;
using namespace AsteroidsManager;

void InitMenu()
{
	background = LoadTexture("Assets/Images/Menu/background.png");
	play = LoadTexture("Assets/Images/Menu/acid.png");
	instructions = LoadTexture("Assets/Images/Menu/ice.png");
	credits = LoadTexture("Assets/Images/Menu/big.png");
	Assets::exit = LoadTexture("Assets/Images/Menu/stone.png");

	font = LoadFont("resources/fonts/romulus.png");


	playPos.x = (screenWidth / 2) - (menuSizeX / 2);
	playPos.y = ((screenHeight / 5)) - (menuSizeY / 2);
	instructionsPos.x = (screenWidth / 2) - (menuSizeX / 2);
	instructionsPos.y = ((screenHeight / 5) * 2) - (menuSizeY / 2);
	creditsPos.x = (screenWidth / 2) - (menuSizeX / 2);
	creditsPos.y = ((screenHeight / 5) * 3) - (menuSizeY / 2);
	exitPos.x = (screenWidth / 2) - (menuSizeX / 2);
	exitPos.y = (screenHeight / 5) * 4 - (menuSizeY / 2);
}

static void GetInput(GameSceen& currentSceen)
{
	int menuSizeX = 200;
	int menuSizeY = 100;
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	if ((mouseX > playPos.x && mouseX < playPos.x + menuSizeX) && (mouseY > playPos.y && mouseY < playPos.y + menuSizeY))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::GAME;
		}
	}
	else if ((mouseX > instructionsPos.x && mouseX < instructionsPos.x + menuSizeX) && (mouseY > instructionsPos.y && mouseY < instructionsPos.y + menuSizeY))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::INSTRUCTIONS;
		}
	}
	else if ((mouseX > creditsPos.x && mouseX < creditsPos.x + menuSizeX) && (mouseY > creditsPos.y && mouseY < creditsPos.y + menuSizeY))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::CREDITS;
		}
	}
	else if ((mouseX > exitPos.x && mouseX < exitPos.x + menuSizeX) && (mouseY > exitPos.y && mouseY < exitPos.y + menuSizeY))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			currentSceen = GameSceen::EXIT;
		}
	}
}

void ShowMenu(GameSceen& currentSceen)
{
	DrawTexture(background, 0, 0, WHITE);
	DrawTextureEx(play, playPos, 0, 1.0, WHITE);
	DrawTextureEx(instructions, instructionsPos, 0, 1.0, WHITE);
	DrawTextureEx(credits, creditsPos, 0, 1.0, WHITE);
	DrawTextureEx(Assets::exit, exitPos, 0, 1.0, WHITE);

	GetInput(currentSceen);
}

void ShowInstructions(GameSceen& currentSceen)
{
	int spacing = 3;

	DrawTexture(background, 0, 0, WHITE);
	/*
	slSetForeColor(0.471f, 0.471f, 0.471f, 1.0f);

	slSetFont(menuFont, 40);
	slText(screenWidth / 2, (screenHeight / 6) * 3, "Use arrows to move");
	slText(screenWidth / 2, (screenHeight / 6) * 4, "Press ESC to go back to the menu");

	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (slGetKey(SL_KEY_ESCAPE))
	{
		currentSceen = MENU;
	}*/
}

void ShowCredits(GameSceen& currentSceen)
{
	/*string credits = "Created by Juan Ignacio Digilio";

	slSprite(menuBackground, screenWidth / 2, screenHeight / 2, screenWidth * 1.2, screenHeight);

	slSetForeColor(0.471f, 0.471f, 0.471f, 1.0f);

	slSetFont(menuFont, 40);
	slText((screenWidth / 2) - (credits.length() / 2), screenHeight / 2, "Created by Juan Ignacio Digilio");

	slSetFont(menuFont, 14);
	slText(screenWidth / 2, 25, "Image Campus student 1st year game development (Sigil evaluation)");

	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (slGetKey(SL_KEY_ESCAPE))
	{
		currentSceen = MENU;
	}*/
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