#pragma once

#include "Asteroids.h"

#include "GameData.h"
#include "Player.h"

#include "raylib.h"
#include "raymath.h"

namespace AsteroidsManager
{
	extern int asteroidsQnty;
	extern int halfAsteroidsQnty;
	extern int quarterAsteroidsQnty;
	extern int activeAsteroids;
	extern int activeHalfs;
	extern int activeCuarters;
	extern float lastDrop;
}

using namespace Globals;
using namespace AsteroidsManager;

void Load(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids);
void Draw(Asteroid* asteroids, int quantity);
void Update(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, Player player);