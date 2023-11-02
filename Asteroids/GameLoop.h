#pragma once

#include "Player.h"
#include "Asteroids.h"
#include "GameData.h"

//namespace Assets
//{
//	extern Sound crash;
//	extern Sound thousand;
//	extern Texture2D pauseButton;
//	extern Texture2D pauseButtonAct;
//
//	extern Vector2 pauseButtonPos;
//}

void Play(Player& player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids, GameSceen& gamseSceen);

void DrawGame(Player player, Asteroid* asteroids, Asteroid* halfAsteroids, Asteroid* quarterAsteroids);
