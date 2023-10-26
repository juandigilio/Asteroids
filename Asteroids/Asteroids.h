#pragma once

#include "GameData.h"
#include "Player.h"

#include "raylib.h"
#include "raymath.h"

using namespace Globals;

static const int asteroidsQnty = 10;
static int activeAsteroids = 0;
static float lastDrop = 0.0f;

struct CuarterAsteroid
{
	Texture2D texture{};
	Vector2 position{};
	Vector2 direction{};
	Vector2 velocity{};
	float speed = 0.04f;
	float rotation = 0.0f;
	bool isAlive = false;

	void Move()
	{
		velocity = Vector2Scale(direction, speed * GetFrameTime());
		position = Vector2Add(position, velocity);

		if (position.x > screenWidth + texture.width / 2)
		{
			position.x = (-texture.width / 2);
			position.y = screenHeight - position.y;
		}
		else if (position.x < 0.0f - texture.width / 2)
		{
			position.x = screenWidth + (texture.width / 2);
			position.y = screenHeight - position.y;
		}
		else if (position.y > screenHeight + texture.height / 2)
		{
			position.x = screenWidth - position.x;
			position.y = (-texture.height / 2);
		}
		else if (position.y < 0.0f - texture.height / 2)
		{
			position.x = screenWidth - position.x;
			position.y = screenHeight + (texture.height / 2);
		}
	}
};

struct MidAsteroid
{
	Texture2D texture{};
	Vector2 position{};
	Vector2 direction{};
	Vector2 velocity{};
	float speed = 0.1f;
	float rotation = 0.0f;
	bool isAlive = false;

	CuarterAsteroid cuarter1{};
	CuarterAsteroid cuarter2{};

	void Move()
	{
		velocity = Vector2Scale(direction, speed * GetFrameTime());
		position = Vector2Add(position, velocity);

		if (position.x > screenWidth + texture.width / 2)
		{
			position.x = (-texture.width / 2);
			position.y = screenHeight - position.y;
		}
		else if (position.x < 0.0f - texture.width / 2)
		{
			position.x = screenWidth + (texture.width / 2);
			position.y = screenHeight - position.y;
		}
		else if (position.y > screenHeight + texture.height / 2)
		{
			position.x = screenWidth - position.x;
			position.y = (-texture.height / 2);
		}
		else if (position.y < 0.0f - texture.height / 2)
		{
			position.x = screenWidth - position.x;
			position.y = screenHeight + (texture.height / 2);
		}
	}
};

struct Asteroid
{
	Texture2D texture{};
	Vector2 position{};
	Vector2 direction{};
	Vector2 velocity{};
	float speed = 120.0f;
	float rotation = 0.0f;
	bool isAlive = false;

	MidAsteroid half1{};
	MidAsteroid half2{};

	void Move()
	{
		velocity = Vector2Scale(direction, speed * GetFrameTime());
		position = Vector2Add(position, velocity);

		if (position.x > screenWidth + texture.width / 2)
		{
			position.x = (-texture.width / 2);
			position.y = screenHeight - position.y;
		}
		else if (position.x < 0.0f - texture.width / 2)
		{
			position.x = screenWidth + (texture.width / 2);
			position.y = screenHeight - position.y;
		}
		else if (position.y > screenHeight + texture.height / 2)
		{
			position.x = screenWidth - position.x;
			position.y = (-texture.height / 2);
		}
		else if (position.y < 0.0f - texture.height / 2)
		{
			position.x = screenWidth - position.x;
			position.y = screenHeight + (texture.height / 2);
		}
	}
};

static void Load(Asteroid asteroids[])
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		asteroids[i].texture = LoadTexture("Assets/Images/asteroid.png");
		asteroids[i].half1.texture = LoadTexture("Assets/Images/halfAsteroid.png");
		asteroids[i].half2.texture = LoadTexture("Assets/Images/halfAsteroid.png");
		asteroids[i].half1.cuarter1.texture = LoadTexture("Assets/Images/cuarterAsteroid.png");
		asteroids[i].half1.cuarter2.texture = LoadTexture("Assets/Images/cuarterAsteroid.png");
		asteroids[i].half2.cuarter1.texture = LoadTexture("Assets/Images/cuarterAsteroid.png");
		asteroids[i].half2.cuarter2.texture = LoadTexture("Assets/Images/cuarterAsteroid.png");
	}
}

static void Spawn(Asteroid& asteroid, Player player)
{
	int spawnPoint;
	int playerSector;

	Vector2 spawner1{ 0.0f,0.0f };
	Vector2 spawner2{ 0.0f, static_cast<float>(screenHeight) };
	Vector2 spawner3{ static_cast<float>(screenWidth),0.0f };
	Vector2 spawner4{ static_cast<float>(screenWidth),static_cast<float>(screenHeight) };

	if (player.position.x < screenWidth / 2 && player.position.y < screenHeight / 2)
	{
		playerSector = 0;
	}
	else if (player.position.x > screenWidth / 2 && player.position.y < screenHeight / 2)
	{
		playerSector = 1;
	}
	else if (player.position.x < screenWidth / 2 && player.position.y > screenHeight / 2)
	{
		playerSector = 2;
	}
	else
	{
		playerSector = 3;
	}

	do
	{
		spawnPoint = rand() % 4;

	} while (spawnPoint == playerSector);

	switch (spawnPoint)
	{
		case 0:
		{
			asteroid.position = spawner1;
			break;
		}
		case 1:
		{
			asteroid.position = spawner2;
			break;
		}
		case 2:
		{
			asteroid.position = spawner3;
			break;
		}
		case 3:
		{
			asteroid.position = spawner4;
			break;
		}
	}

	asteroid.direction = Vector2Subtract(player.position, asteroid.position);
	float length = Vector2Length(asteroid.direction);
	asteroid.direction = Vector2Divide(asteroid.direction, { length, length });

	asteroid.isAlive = true;
	asteroid.half1.isAlive = true;
	asteroid.half1.cuarter1.isAlive = true;
	asteroid.half1.cuarter2.isAlive = true;
	asteroid.half2.isAlive = true;
	asteroid.half2.cuarter1.isAlive = true;
	asteroid.half2.cuarter2.isAlive = true;
}

static void Draw(Asteroid asteroids[])
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		if (asteroids[i].isAlive)
		{
			DrawTextureV(asteroids[i].texture, asteroids[i].position, RAYWHITE);
		}
		else
		{
			if (asteroids[i].half1.isAlive)
			{
				DrawTextureV(asteroids[i].half1.texture, asteroids[i].position, RAYWHITE);
			}
			else
			{
				if (asteroids[i].half1.cuarter1.isAlive)
				{
					DrawTextureV(asteroids[i].half1.cuarter1.texture, asteroids[i].position, RAYWHITE);
				}

				if (asteroids[i].half1.cuarter2.isAlive)
				{
					DrawTextureV(asteroids[i].half1.cuarter2.texture, asteroids[i].position, RAYWHITE);
				}
			}

			if (asteroids[i].half2.isAlive)
			{
				DrawTextureV(asteroids[i].half2.texture, asteroids[i].position, RAYWHITE);
			}
			else
			{
				if (asteroids[i].half2.cuarter1.isAlive)
				{
					DrawTextureV(asteroids[i].half2.cuarter1.texture, asteroids[i].position, RAYWHITE);
				}

				if (asteroids[i].half2.cuarter2.isAlive)
				{
					DrawTextureV(asteroids[i].half2.cuarter2.texture, asteroids[i].position, RAYWHITE);
				}
			}
		}
	}
}

static bool IsACtive(Asteroid asteroid)
{
	if (!asteroid.half1.cuarter1.isAlive && !asteroid.half1.cuarter2.isAlive && !asteroid.half2.cuarter1.isAlive && !asteroid.half2.cuarter2.isAlive)
	{
		return false;
	}
	else
	{
		return true;
	}
}

static void Update(Asteroid asteroids[], Player player)
{
	float elapsedTime = GetTime() - lastDrop;

	if (activeAsteroids < asteroidsQnty && elapsedTime > 3.0f)
	{
		for (int i = 0; i < asteroidsQnty; i++)
		{
			if (!IsACtive(asteroids[i]))
			{
				Spawn(asteroids[i], player);
				activeAsteroids++;
				lastDrop = GetTime();
				std::cout << "Active instances: " << activeAsteroids << std::endl;
				break;
			}
		}
	}



	for (int i = 0; i < asteroidsQnty; i++)
	{
		if (asteroids[i].isAlive)
		{
			asteroids[i].Move();
		}
		else
		{
			if (asteroids[i].half1.isAlive)
			{
				asteroids[i].half1.Move();
			}
			else
			{
				if (asteroids[i].half1.cuarter1.isAlive)
				{
					asteroids[i].half1.cuarter1.Move();
				}

				if (asteroids[i].half1.cuarter2.isAlive)
				{
					asteroids[i].half1.cuarter2.Move();
				}
			}

			if (asteroids[i].half2.isAlive)
			{
				asteroids[i].half2.Move();
			}
			else
			{
				if (asteroids[i].half2.cuarter1.isAlive)
				{
					asteroids[i].half2.cuarter1.Move();
				}

				if (asteroids[i].half2.cuarter2.isAlive)
				{
					asteroids[i].half2.cuarter2.Move();
				}
			}
		}
	}
}