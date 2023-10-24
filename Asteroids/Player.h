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
	Texture2D texture;
};

//void GetInput(Player& player)
//{
//
//}