#pragma once

#include "raylib.h"


struct Player
{
	Vector2 position;
	float speed;
	float rotation;
	int totalPoints;
	int availableLives;
	bool isAlive;
	Texture2D texture;
};

struct Asteroid
{
	Vector2 position;

};