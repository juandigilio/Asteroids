#include "GameLoop.h"

#include "AsteroidsManager.h"

#include "raymath.h"

namespace Assets
{
	extern Sound crash{};
	
	extern Texture2D pauseButton{};
	extern Texture2D pauseButtonAct{};

	extern Vector2 pauseButtonPos{};
}

using namespace AsteroidsManager;
using namespace Assets;

static Texture2D gamePlayBacground{};

static void LoadGame()
{
	gamePlayBacground = LoadTexture("Assets/Images/background.png");

	crash = LoadSound("Assets/Sounds/crash.wav");
	
	pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
	pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

	pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
	pauseButtonPos.y = 15.0f;
}

static void PlayerCollides(Player& player, GameSceen& gamseSceen)
{
	player.isColliding = true;
	player.lastCollide = static_cast<float>(GetTime());
	player.availableLives--;
	PlaySound(crash);

	if (player.totalPoints > highScore)
	{
		highScore = player.totalPoints;
	}
	
	if (player.availableLives == 0)
	{
		gamseSceen = GameSceen::RESULTS;
	}
}

static void KillAsteroid(Asteroid& asteroid, Bullet& bullet, int& actives)
{
	asteroid.isAlive = false;
	actives--;
	bullet.isAlive = false;
}

static bool CheckCircleCircleCollision(float radius1, float radius2, Vector2 position1, Vector2 position2)
{
	float actualDistance = Vector2Distance(position1, position2);
	float minDistance = radius1 + radius2;

	if (actualDistance <= minDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

static void CheckAsteroidsVsEntities(Player& player, Asteroid* asteroids, Asteroid* toSpawn, int& astQnty, int& actAsteroids, int& activesToSpawn, int& maxToSpawn, GameSceen& currentSceen, bool isQuarter)
{
	for (int i = 0; i < astQnty; i++)
	{
		if (asteroids[i].isAlive)
		{
			if (CheckCircleCircleCollision(player.radius, asteroids[i].radius, player.GetCenter(), asteroids[i].GetCenter()))
			{
				PlayerCollides(player, currentSceen);
			}
			else
			{
				for (int j = 0; j < maxBulletsQnty; j++)
				{
					if (player.bullets[j].isAlive)
					{
						if (CheckCircleCircleCollision(player.bullets[j].radius, asteroids[i].radius, player.bullets[j].GetCenter(), asteroids[i].GetCenter()))
						{
							KillAsteroid(asteroids[i], player.bullets[j], actAsteroids);

							player.totalPoints += 30;

							if (!isQuarter)
							{
								SpawnChildrens(player.bullets[j], asteroids[i], toSpawn, activesToSpawn, maxToSpawn);
								player.totalPoints += 20;
							}
						}
					}
				}
			}
		}
	}
}

static void AsteroidsRebound(Asteroid& asteroid1, Asteroid& asteroid2)
{
	Vector2 collisionVector = Vector2Subtract(asteroid1.position, asteroid2.position);

	float collisionAngle = static_cast<float>(atan2(collisionVector.y, collisionVector.x));

	asteroid1.direction = Vector2Rotate(asteroid1.direction, (180.0f - collisionAngle) * RAD2DEG);
	asteroid2.direction = Vector2Rotate(asteroid2.direction, (180.0f - collisionAngle) * RAD2DEG);

	asteroid1.isColliding = true;
	asteroid1.lastCollide = static_cast<float>(GetTime());
	asteroid2.isColliding = true;
	asteroid2.lastCollide = static_cast<float>(GetTime());
}

static void CheckAsteroidsVsAsteroids(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		if (asteroids[i].isAlive && !asteroids[i].isSpawning && !asteroids[i].isColliding)
		{
			for (int j = 0; j < asteroidsQnty; j++)
			{
				if (asteroids[j].isAlive && i != j && !asteroids[j].isSpawning && !asteroids[j].isColliding)
				{
					if (CheckCircleCircleCollision(asteroids[i].radius, asteroids[j].radius, asteroids[i].GetCenter(), asteroids[j].GetCenter()))
					{
						AsteroidsRebound(asteroids[i], asteroids[j]);
						break;
					}
				}
			}

			for (int j = 0; j < halfAsteroidsQnty; j++)
			{
				if (halfAsteroids[j].isAlive && !halfAsteroids[j].isSpawning && !halfAsteroids[j].isColliding)
				{
					if (CheckCircleCircleCollision(asteroids[i].radius, halfAsteroids[j].radius, asteroids[i].GetCenter(), halfAsteroids[j].GetCenter()))
					{
						AsteroidsRebound(asteroids[i], halfAsteroids[j]);
						break;
					}
				}
			}

			for (int j = 0; j < quarterAsteroidsQnty; j++)
			{
				if (quarterAsteroids[j].isAlive && !quarterAsteroids[j].isSpawning && !quarterAsteroids[j].isColliding)
				{
					if (CheckCircleCircleCollision(asteroids[i].radius, quarterAsteroids[j].radius, asteroids[i].GetCenter(), quarterAsteroids[j].GetCenter()))
					{
						AsteroidsRebound(asteroids[i], quarterAsteroids[j]);
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		if (halfAsteroids[i].isAlive && !halfAsteroids[i].isSpawning && !halfAsteroids[i].isColliding)
		{
			for (int j = 0; j < halfAsteroidsQnty; j++)
			{
				if (halfAsteroids[j].isAlive && i != j && !halfAsteroids[j].isSpawning && !halfAsteroids[j].isColliding)
				{
					if (CheckCircleCircleCollision(halfAsteroids[i].radius, halfAsteroids[j].radius, halfAsteroids[i].GetCenter(), halfAsteroids[j].GetCenter()))
					{
						AsteroidsRebound(halfAsteroids[i], halfAsteroids[j]);
						break;
					}
				}
			}

			for (int j = 0; j < quarterAsteroidsQnty; j++)
			{
				if (quarterAsteroids[j].isAlive && !quarterAsteroids[j].isSpawning && !quarterAsteroids[j].isColliding)
				{
					if (CheckCircleCircleCollision(halfAsteroids[i].radius, quarterAsteroids[j].radius, halfAsteroids[i].GetCenter(), quarterAsteroids[j].GetCenter()))
					{
						AsteroidsRebound(halfAsteroids[i], quarterAsteroids[j]);
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		if (quarterAsteroids[i].isAlive && !quarterAsteroids[i].isSpawning && !quarterAsteroids[i].isColliding)
		{
			for (int j = 0; j < quarterAsteroidsQnty; j++)
			{
				if (quarterAsteroids[j].isAlive && i != j && !quarterAsteroids[j].isSpawning && !quarterAsteroids[j].isColliding)
				{
					if (CheckCircleCircleCollision(quarterAsteroids[i].radius, quarterAsteroids[j].radius, quarterAsteroids[i].GetCenter(), quarterAsteroids[j].GetCenter()))
					{
						AsteroidsRebound(quarterAsteroids[i], quarterAsteroids[j]);
						break;
					}
				}
			}
		}
	}
}

static void UpdateCollisions(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	CheckAsteroidsVsEntities(player, asteroids, halfAsteroids, asteroidsQnty, activeAsteroids, activeHalfs, halfAsteroidsQnty, gamseSceen, false);

	CheckAsteroidsVsEntities(player, halfAsteroids, quarterAsteroids, halfAsteroidsQnty, activeHalfs, activeQuarters, quarterAsteroidsQnty, gamseSceen, false);

	CheckAsteroidsVsEntities(player, quarterAsteroids, quarterAsteroids, quarterAsteroidsQnty, activeQuarters, quarterAsteroidsQnty, quarterAsteroidsQnty, gamseSceen, true);

	CheckAsteroidsVsAsteroids(asteroids, halfAsteroids, quarterAsteroids);
}

static void UpdateAll(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	UpdateAsteroids(asteroids, halfAsteroids, quarterAsteroids, player);
	UpdatePlayer(player);
	UpdateCollisions(player, asteroids, halfAsteroids, quarterAsteroids, gamseSceen);
	UpdateMusicStream(gameLoopMusic);
}

static void RestartAllEntities(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	player.position.x = screenCenter.x - (player.texture.width / 2);
	player.position.y = screenCenter.y - (player.texture.height / 2);
	player.velocity = { 0, 0 };
	player.speed = 0;
	player.totalPoints = 0;
	player.thousandCouner = 0;

	for (int i = 0; i < maxBulletsQnty; i++)
	{
		player.bullets[i].isAlive = false;
		player.bullets[i].firstCrossing = true;
	}

	for (int i = 0; i < asteroidsQnty; i++)
	{
		asteroids[i].isAlive = false;
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		halfAsteroids[i].isAlive = false;
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		quarterAsteroids[i].isAlive = false;
	}

	activeAsteroids = 0;
	activeHalfs = 0;
	activeQuarters = 0;
}

static void ShowCrash(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	player.rotation += 0.6f;

	if (player.rotation >= 360.0f)
	{
		player.rotation = 0.0f;
	}

	if (GetTime() - player.lastCollide > 2.0f)
	{
		player.isColliding = false;

		RestartAllEntities(player, asteroids, halfAsteroids, quarterAsteroids);
	}
}

static void GetHUDInput(GameSceen& currentSceen)
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	if (currentSceen == GameSceen::GAME)
	{
		if ((mouseX > pauseButtonPos.x && mouseX < pauseButtonPos.x + pauseButton.width) && (mouseY > pauseButtonPos.y && mouseY < pauseButtonPos.y + pauseButton.height))
		{
			DrawTextureEx(pauseButtonAct, pauseButtonPos, 0, 1.0, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentSceen = GameSceen::PAUSE;
			}
		}
	}
}

static void DrawHUD(Player player)
{
	Vector2 textPos;

	textPos.x = 15;
	textPos.y = screenHeight - fontSize ;
	DrawTextEx(font, "Score: ", textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

	textPos.x += MeasureTextEx(font, "Score: ", fontSize * 0.25f, spacing / 8.0f).x;
	DrawTextEx(font, TextFormat("%01i", player.totalPoints), textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

	textPos.x = 15;
	textPos.y += 20;
	DrawTextEx(font, "High score: ", textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

	textPos.x += MeasureTextEx(font, "High score: ", fontSize * 0.25f, spacing / 8.0f).x;
	DrawTextEx(font, TextFormat("%01i", highScore), textPos, fontSize * 0.25f, spacing / 8.0f, RAYWHITE);

	DrawTextureEx(pauseButton, pauseButtonPos, 0, 1.0, WHITE);
}

void DrawGame(Player player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	DrawTextureV(gamePlayBacground, {0, 0}, RAYWHITE);
	DrawPlayer(player);
	DrawAsteroids(asteroids, asteroidsQnty);
	DrawAsteroids(halfAsteroids, halfAsteroidsQnty);
	DrawAsteroids(quarterAsteroids, quarterAsteroidsQnty);
	DrawHUD(player);
}

static void GameLoop(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& currentSceen)
{
	if (!player.isColliding)
	{
		GetPlayerInput(player, currentSceen);

		UpdateAll(player, asteroids, halfAsteroids, quarterAsteroids, currentSceen);
	}
	else
	{
		ShowCrash(player, asteroids, halfAsteroids, quarterAsteroids);
	}

	DrawGame(player, asteroids, halfAsteroids, quarterAsteroids);

	GetHUDInput(currentSceen);
}

void Play(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& currentSceen)
{
	if (loading)
	{
		LoadGame();
		LoadPlayer(player);
		LoadAsteroids(asteroids, halfAsteroids, quarterAsteroids);
		RestartAllEntities(player, asteroids, halfAsteroids, quarterAsteroids);
		loading = false;
	}
	
	GameLoop(player, asteroids, halfAsteroids, quarterAsteroids, currentSceen);
}