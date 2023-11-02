#pragma once

#include "Asteroids.h"
#include "Player.h"


namespace AsteroidsManager
{
	extern int asteroidsQnty;
	extern int halfAsteroidsQnty;
	extern int quarterAsteroidsQnty;
	extern int activeAsteroids;
	extern int activeHalfs;
	extern int activeQuarters;
	extern float lastDrop;
}

using namespace Globals;
using namespace AsteroidsManager;

void LoadAsteroids(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids);
void DrawAsteroids(Asteroid* asteroids, int quantity);
void UpdateAsteroids(Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, Player player);
void SpawnChildrens(Bullet bullet, Asteroid& brocken, Asteroid* toSpawn, int& actives, int& maxQnty);