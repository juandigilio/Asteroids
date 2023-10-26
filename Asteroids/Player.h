#pragma once

#include "GameData.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>

using namespace Globals;


struct Player
{
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;
	float speed = 0.0f;
	float rotation = 0.0f;
    float targetRotation;
	int totalPoints = 0;
	int availableLives = 3;
    bool isAlive = true;;
	Texture2D texture;
};

static void Load(Player& player)
{
    player.texture = LoadTexture("Assets/Images/ship.png");
    player.position.x = screenWidth / 2;
    player.position.y = screenHeight / 2;
}

static void GetInput(Player& player, GameSceen& currentSceen)
{
    const float interpolationFactor = 0.0015f;

    player.rotation = (atan2(static_cast<double>(GetMousePosition().y) - player.position.y, static_cast<double>(GetMousePosition().x) - player.position.x)) * RAD2DEG + 90;

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        player.speed += 0.0001;

        if (player.speed >= 0.08f)
        {
            player.speed = 0.08f;
        }

        Vector2 targetDirection = Vector2Subtract(GetMousePosition(), player.position);
        float targetLength = Vector2Length(targetDirection);

        targetDirection = Vector2Divide(targetDirection, { targetLength, targetLength });

        player.direction = Vector2Lerp(player.direction, targetDirection, interpolationFactor);

        float length = Vector2Length(player.direction);

        if (length > 0.1)
        {
            player.direction = Vector2Divide(player.direction, { length, length });
        }
    }

    if (IsKeyDown(KEY_ESCAPE))
    {
        currentSceen = GameSceen::MENU;
    }
}

static void Update(Player& player)
{
    player.velocity = Vector2Scale(player.direction, player.speed);

    player.position = Vector2Add(player.position, player.velocity);
}

static void Draw(Player& player)
{
    DrawTexturePro(player.texture, { 0, 0, 221, 264 }, { player.position.x, player.position.y, 221, 264 }, { 110, 132 }, player.rotation, WHITE);
}