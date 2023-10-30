#include "AsteroidsManager.h"


namespace AsteroidsManager
{
	extern int asteroidsQnty = 10;
	extern int halfAsteroidsQnty = asteroidsQnty * 2;
	extern int quarterAsteroidsQnty = halfAsteroidsQnty * 2;
	extern int activeAsteroids = 0;
	extern int activeHalfs = 0;
	extern int activeCuarters = 0;
	extern float lastDrop = 0.0f;
}


void Load(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids)
{
	for (int i = 0; i < asteroidsQnty; i++)
	{
		asteroids[i].texture = LoadTexture("Assets/Images/asteroid.png");
		asteroids[i].radius = asteroids[i].texture.width / 2;
	}

	for (int i = 0; i < halfAsteroidsQnty; i++)
	{
		halfAsteroids[i].texture = LoadTexture("Assets/Images/halfAsteroid.png");
		halfAsteroids[i].radius = halfAsteroids[i].texture.width / 2;
	}

	for (int i = 0; i < quarterAsteroidsQnty; i++)
	{
		quarterAsteroids[i].texture = LoadTexture("Assets/Images/cuarterAsteroid.png");
		quarterAsteroids[i].radius = quarterAsteroids[i].texture.width / 2;
	}
}

static void SpawnBig(Asteroid& asteroid, Player player)
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
}

static void SpawnHalfs(Asteroid& asteroid, Asteroid* halfAsteroids)
{
	int counter = 0;

	for (int i = 0; i < asteroidsQnty; i++)
	{

	}
}

static void Move(Asteroid* asteroids, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		if (asteroids[i].isAlive)
		{
			asteroids[i].velocity = Vector2Scale(asteroids[i].direction, asteroids[i].speed * GetFrameTime());
			asteroids[i].position = Vector2Add(asteroids[i].position, asteroids[i].velocity);

			if (asteroids[i].position.x > screenWidth + asteroids[i].texture.width / 2)
			{
				asteroids[i].position.x = (-asteroids[i].texture.width / 2);
				asteroids[i].position.y = screenHeight - asteroids[i].position.y;
			}
			else if (asteroids[i].position.x < 0.0f - asteroids[i].texture.width / 2)
			{
				asteroids[i].position.x = screenWidth + (asteroids[i].texture.width / 2);
				asteroids[i].position.y = screenHeight - asteroids[i].position.y;
			}
			else if (asteroids[i].position.y > screenHeight + asteroids[i].texture.height / 2)
			{
				asteroids[i].position.x = screenWidth - asteroids[i].position.x;
				asteroids[i].position.y = (-asteroids[i].texture.height / 2);
			}
			else if (asteroids[i].position.y < 0.0f - asteroids[i].texture.height / 2)
			{
				asteroids[i].position.x = screenWidth - asteroids[i].position.x;
				asteroids[i].position.y = screenHeight + (asteroids[i].texture.height / 2);
			}
		}
	}
}

void Draw(Asteroid* asteroids, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		if (asteroids[i].isAlive)
		{
			DrawTextureV(asteroids[i].texture, asteroids[i].GetCenter(), RAYWHITE);
		}
	}
}

void Update(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, Player player)
{
	float elapsedTime = GetTime() - lastDrop;

	if (activeAsteroids < asteroidsQnty && elapsedTime > 3.0f)
	{
		for (int i = 0; i < asteroidsQnty; i++)
		{
			if (!asteroids[i].isAlive)
			{
				SpawnBig(asteroids[i], player);
				activeAsteroids++;
				asteroids[i].isAlive = true;
				lastDrop = GetTime();
				std::cout << "Active instances: " << activeAsteroids << std::endl;
				break;
			}
		}
	}

	Move(asteroids, asteroidsQnty);
	Move(halfAsteroids, halfAsteroidsQnty);
	Move(quarterAsteroids, quarterAsteroidsQnty);
}
