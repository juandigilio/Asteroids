#pragma once

#include "raylib.h"


struct Player
{
	Vector2 position;
	Vector2 velocity;
	float speed;
	float rotation;
	int totalPoints;
	int availableLives;
	bool isAlive;
	bool isMoving;
	Texture2D texture;

	void Acelerate()
	{
		speed += 0.0001;

		if (speed >= 0.15f)
		{
			speed = 0.15f;
		}
	}
};

struct Asteroid
{
	Vector2 position;

};