#pragma once

#include "raylib.h"

struct Asteroid
{
	Texture2D texture{};
	Vector2 position{};
	Vector2 direction{};
	Vector2 velocity{};
	float speed = 120.0f;
	float mass{};
	float rotation = 0.0f;
	float radius;
	bool isAlive = false;
	bool isSpawning = false;
	float lastSpawn = 0.0f;
	bool isColliding = false;
	float lastCollide = 0.0f;
	
	Vector2 GetCenter()
	{
		return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
	}
};

