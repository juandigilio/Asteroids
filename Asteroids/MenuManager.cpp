#include "MenuManager.h"



#include "raylib.h"

#include "GameData.h"
#include "Entities.h"
//#include "GameLoop.h"

using namespace Globals;
using namespace MenuAssets;

void InitMenu()
{

	background = LoadTexture("../Assets/Images/Menu/background.png");
	play = LoadTexture("../Assets/Images/Menu/acid.png");
	instructions = LoadTexture("../Assets/Images/Menu/ice.png");
	credits = LoadTexture("../Assets/Images/Menu/big.png");
	exit = LoadTexture("../Assets/Images/Menu/stone.png");

	//menuFont = slLoadFont("../Assets/Fonts/DelaGothic.ttf");

	//slSetTextAlign(SL_ALIGN_CENTER);

	playPos.x = screenWidth / 2;
	playPos.y = ((screenHeight / 5) * 4);
	instructionsPos.x = screenWidth / 2;
	instructionsPos.y = ((screenHeight / 5) * 3);
	creditsPos.x = screenWidth / 2;
	creditsPos.y = ((screenHeight / 5) * 2);
	exitPos.x = (screenWidth / 2);
	exitPos.y = (screenHeight / 5);
}

void Draw()
{
	DrawTexture(background, 0, 0, WHITE);
	DrawTextureEx(play, playPos, 0, 1.0, WHITE);
	DrawTextureEx(instructions, instructionsPos, 0, 1.0, WHITE);
	DrawTextureEx(credits, creditsPos, 0, 1.0, WHITE);
	DrawTextureEx(exit, exitPos, 0, 1.0, WHITE);

	/*slSprite(menuBackground, screenWidth / 2, screenHeight / 2, screenWidth * 1.2, screenHeight);
	slSprite(acidBrick, acidPosX, acidPosY, menuSizeX, menuSizeY);
	slSprite(iceBrick, icePosX, icePosY, menuSizeX, menuSizeY);
	slSprite(bigBrick, bigPosX, bigPosY, menuSizeX, menuSizeY);
	slSprite(stoneBrick, stonePosX, stonePosY, menuSizeX, menuSizeY);

	slSetForeColor(0.471f, 0.471f, 0.471f, 1.0f);

	slSetFont(menuFont, 45);
	slText(acidPosX, acidPosY - 6, "Play");

	slSetFont(menuFont, 40);
	slText(stonePosX - 3, stonePosY - 22, "Exit");

	slSetFont(menuFont, 30);
	slText(bigPosX, bigPosY - 9, "Credits");

	slSetFont(menuFont, 25);
	slText(icePosX, icePosY - 6, "Istructions");

	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);*/
}

void GetInput(GameSceen& currentSceen)
{
	/*slSetForeColor(1.0f, 0.47f, 0.0f, 1.0f);

	if ((slGetMouseX() > acidPosX - menuSizeX / 2 && slGetMouseX() < acidPosX + menuSizeX / 2) &&
		(slGetMouseY() > acidPosY - menuSizeY / 2 && slGetMouseY() < acidPosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 45);
		slText(acidPosX, acidPosY - 6, "Play");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = GAME;
		}
	}
	else if ((slGetMouseX() > stonePosX - menuSizeX / 2 && slGetMouseX() < stonePosX + menuSizeX / 2) &&
		(slGetMouseY() > stonePosY - menuSizeY / 2 && slGetMouseY() < stonePosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 40);
		slText(stonePosX - 3, stonePosY - 22, "Exit");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = EXIT;
		}
	}
	else if ((slGetMouseX() > bigPosX - menuSizeX / 2 && slGetMouseX() < bigPosX + menuSizeX / 2) &&
		(slGetMouseY() > bigPosY - menuSizeY / 2 && slGetMouseY() < bigPosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 30);
		slText(bigPosX, bigPosY - 9, "Credits");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = CREDITS;
		}
	}
	else if ((slGetMouseX() > icePosX - menuSizeX / 2 && slGetMouseX() < icePosX + menuSizeX / 2) &&
		(slGetMouseY() > icePosY - menuSizeY / 2 && slGetMouseY() < icePosY + menuSizeY / 2))
	{
		slSetFont(menuFont, 25);
		slText(icePosX, icePosY - 6, "Istructions");

		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			currentSceen = INSTRUCTIONS;
		}
	}


	slSetForeColor(1.0f, 1.0f, 1.0f, 1.0f);*/
}

void ShowMenu(GameSceen& currentSceen)
{
	Draw();

	GetInput(currentSceen);
}

void ShowInstructions(GameSceen& currentSceen)
{
	/*slSprite(menuBackground, screenWidth / 2, screenHeight / 2, screenWidth * 1.2, screenHeight);

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
	GameSceen currentSceen = MENU;
	Player player;

	InitWindow(screenWidth, screenHeight, "After-Roids");

	InitMenu();


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentSceen)
		{
			case MENU:
			{
				ShowMenu(currentSceen);
				break;
			}
			case GAME:
			{
				//Play(player, ball, bricks, currentSceen);
				break;
			}
			case INSTRUCTIONS:
			{
				ShowInstructions(currentSceen);
				break;
			}
			case CREDITS:
			{
				ShowCredits(currentSceen);
				break;
			}
			case EXIT:
			{
				CloseWindow();
				break;
			}
		}

		EndDrawing();
	}


}