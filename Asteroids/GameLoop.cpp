#include "GameLoop.h"

#include "AsteroidsManager.h"

#include "raymath.h"

using namespace AsteroidsManager;

static Texture2D gamePlayBacground{};

bool CheckCollision(float radius1, float radius2, Vector2 position1, Vector2 position2)
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

static void PlayerCollides(Player& player, GameSceen& gamseSceen)
{
	player.isColliding = true;
	player.lastCollide = GetTime();
	player.availableLives--;

	if (player.availableLives == 2)
	{
		player.totalPoints = -150;
	}
	else if (player.availableLives == 1)
	{
		player.totalPoints = -300;
	}
	else
	{
		gamseSceen = GameSceen::RESULTS;
	}
}

void UpdateCollisions(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		if (asteroids[i].isAlive)
		{
			if (CheckCollision(player.radius, asteroids[i].radius, player.GetCenter(), asteroids[i].GetCenter()))
			{
				PlayerCollides(player, gamseSceen);
				//std::cout << "player crash big" << std::endl;
			}
			else
			{
				for (int j = 0; j < maxBulletsQnty; j++)
				{
					if (player.bullets[j].isAlive && CheckCollision(player.bullets[j].radius, asteroids[i].radius, player.bullets[j].GetCenter(), asteroids[i].GetCenter()))
					{
						asteroids[i].isAlive = false;
						activeAsteroids--;
						player.bullets[j].isAlive = false;
						SpawnChildrens(player.bullets[j], asteroids[i], halfAsteroids, activeHalfs, halfAsteroidsQnty);
					}
				}
			}
		}
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		if (halfAsteroids[i].isAlive)
		{
			if (CheckCollision(player.radius, halfAsteroids[i].radius, player.GetCenter(), halfAsteroids[i].GetCenter()))
			{
				PlayerCollides(player, gamseSceen);
				//std::cout << "player crash half" << std::endl;
			}
			else
			{
				for (int j = 0; j < maxBulletsQnty; j++)
				{
					if (player.bullets[j].isAlive && CheckCollision(player.bullets[j].radius, halfAsteroids[i].radius, player.bullets[j].GetCenter(), halfAsteroids[i].GetCenter()))
					{
						halfAsteroids[i].isAlive = false;
						activeHalfs--;
						player.bullets[j].isAlive = false;
						SpawnChildrens(player.bullets[j], halfAsteroids[i], quarterAsteroids, activeQuarters, quarterAsteroidsQnty);
					}
				}
			}
		}
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		if (quarterAsteroids[i].isAlive)
		{
			if (CheckCollision(player.radius, quarterAsteroids[i].radius, player.GetCenter(), quarterAsteroids[i].GetCenter()))
			{
				PlayerCollides(player, gamseSceen);
				//std::cout << "player crash quarter" << std::endl;
			}
			else
			{
				for (int j = 0; j < maxBulletsQnty; j++)
				{
					if (player.bullets[j].isAlive && CheckCollision(player.bullets[j].radius, quarterAsteroids[i].radius, player.bullets[j].GetCenter(), quarterAsteroids[i].GetCenter()))
					{
						quarterAsteroids[i].isAlive = false;
						activeQuarters--;
						player.bullets[j].isAlive = false;
					}
				}
			}
		}
	}
}

static void UpdateAll(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	Update(asteroids, halfAsteroids, quarterAsteroids, player);
	Update(player);

	UpdateCollisions(player, asteroids, halfAsteroids, quarterAsteroids, gamseSceen);
}

static void RestartAllEntities(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	player.position.x = screenCenter.x - (player.texture.width / 2);
	player.position.y = screenCenter.y - (player.texture.height / 2);
	player.velocity = { 0, 0 };
	player.speed = 0;

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

void ShowCrash(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
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

static void Draw(Player player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	DrawTextureV(gamePlayBacground, {0, 0}, RAYWHITE);
	Draw(player);
	Draw(asteroids, asteroidsQnty);
	Draw(halfAsteroids, halfAsteroidsQnty);
	Draw(quarterAsteroids, quarterAsteroidsQnty);
}

void GameLoop(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	if (!player.isColliding)
	{
		GetInput(player, gamseSceen);

		UpdateAll(player, asteroids, halfAsteroids, quarterAsteroids, gamseSceen);
	}
	else
	{
		ShowCrash(player, asteroids, halfAsteroids, quarterAsteroids);
	}

	Draw(player, asteroids, halfAsteroids, quarterAsteroids);
}

void Play(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen)
{
	if (loading)
	{
		gamePlayBacground = LoadTexture("Assets/Images/background.png");
		Load(player);
		Load(asteroids, halfAsteroids, quarterAsteroids);
		loading = false;
	}
	
	GameLoop(player, asteroids, halfAsteroids, quarterAsteroids, gamseSceen);
}