#pragma once

#include "raylib.h"
struct CuarterAsteroid
{
	Texture2D texture;
	bool isAlive = true;
};

struct MidAsteroid
{
	Texture2D texture;
	bool isAlive = true;

	CuarterAsteroid cuarter1;
	CuarterAsteroid cuarter2;
};

struct Asteroid
{
	Texture2D texture;
	bool isAlive = true;

	MidAsteroid half1;
	MidAsteroid half2;
};