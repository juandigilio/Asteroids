#pragma once

#include "GameData.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>

using namespace Globals;

const int maxBulletsQnty = 30;

struct Bullet
{
    Vector2 position{};
    Vector2 velocity{};
    Vector2 direction{};
    float speed = 280.0f;
    bool firstCrossing = true;
    bool isAlive = false;
    Texture2D texture;
};

struct Player
{
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;
	float speed = 0.0f;
    float maxSpeed = 120.0f;
	float rotation = 0.0f;
    float targetRotation;
	int totalPoints = 0;
	int availableLives = 3;
    bool isAlive = true;
	Texture2D texture;

    Bullet bullets[maxBulletsQnty];

    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
    }
};

static void Load(Player& player)
{
    player.texture = LoadTexture("Assets/Images/ship.png");
    player.position.x = screenWidth / 2;
    player.position.y = screenHeight / 2;

    for (int i = 0; i < maxBulletsQnty; i++)
    {
        player.bullets[i].texture = LoadTexture("Assets/Images/bullet.png");
        player.bullets[i].isAlive = false;
    }
}

static void Shoot(Player& player)
{
    for (int i = 0; i < maxBulletsQnty; i++)
    {
        if (!player.bullets[i].isAlive)
        {
            std::cout << "esta disparando" << std::endl;
            player.bullets[i].position = player.position;
            player.bullets[i].isAlive = true;
            player.bullets[i].firstCrossing = true;

            player.bullets[i].direction = Vector2Subtract(GetMousePosition(), player.bullets[i].position);
            float length = Vector2Length(player.bullets[i].direction);

            player.bullets[i].direction = Vector2Divide(player.bullets[i].direction, { length, length });

            break;
        }
    }
}

static void MovePlayer(Player& player)
{
    player.velocity = Vector2Scale(player.direction, player.speed * GetFrameTime());
    player.position = Vector2Add(player.position, player.velocity);

    if (player.position.x > screenWidth + player.texture.width / 2)
    {
        player.position.x = (-player.texture.width / 2);
        player.position.y = screenHeight - player.position.y;
    }
    else if (player.position.x < 0.0f - player.texture.width / 2)
    {
        player.position.x = screenWidth + (player.texture.width / 2);
        player.position.y = screenHeight - player.position.y;
    }
    else if (player.position.y > screenHeight + player.texture.height / 2)
    {
        player.position.x = screenWidth - player.position.x;
        player.position.y = (-player.texture.height / 2);
    }
    else if (player.position.y < 0.0f - player.texture.height / 2)
    {
        player.position.x = screenWidth - player.position.x;
        player.position.y = screenHeight + (player.texture.height / 2);
    }
}

static void MoveBullets(Bullet& bullet)
{
    bullet.velocity = Vector2Scale(bullet.direction, bullet.speed * GetFrameTime());
    bullet.position = Vector2Add(bullet.position, bullet.velocity);

    if (bullet.position.x > screenWidth + bullet.texture.width / 2)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = (-bullet.texture.width / 2);
            bullet.position.y = screenHeight - bullet.position.y;
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
        }
    }
    else if (bullet.position.x < 0.0f - bullet.texture.width / 2)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = screenWidth + (bullet.texture.width / 2);
            bullet.position.y = screenHeight - bullet.position.y;
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
        }
    }
    else if (bullet.position.y > screenHeight + bullet.texture.height / 2)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = screenWidth - bullet.position.x;
            bullet.position.y = (-bullet.texture.height / 2);
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
        }
    }
    else if (bullet.position.y < 0.0f - bullet.texture.height / 2)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = screenWidth - bullet.position.x;
            bullet.position.y = screenHeight + (bullet.texture.height / 2);
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
        }
    }
}

static void GetInput(Player& player, GameSceen& currentSceen)
{
    const float interpolationFactor = 0.0014f;

    player.rotation = (atan2(static_cast<double>(GetMousePosition().y) - player.position.y, static_cast<double>(GetMousePosition().x) - player.position.x)) * RAD2DEG + 90;

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        player.speed += 0.05;

        if (player.speed >= player.maxSpeed)
        {
            player.speed = player.maxSpeed;
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

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        std::cout << "disparo" << std::endl;
        Shoot(player);
    }

    if (IsKeyDown(KEY_ESCAPE))
    {
        currentSceen = GameSceen::MENU;
    }
}

static void Update(Player& player)
{
    MovePlayer(player);

    for (int i = 0; i < maxBulletsQnty; i++)
    {
        if (player.bullets[i].isAlive)
        {
            MoveBullets(player.bullets[i]);
        }
    }
}

static void Draw(Player& player)
{
    DrawTexturePro(player.texture, { 0, 0, 221, 264 }, { player.position.x, player.position.y, 221, 264 }, { 110, 132 }, player.rotation, WHITE);

    for (int i = 0; i < maxBulletsQnty; i++)
    {
        if (player.bullets[i].isAlive)
        {
            std::cout << "esta viva" << i << std::endl;

            DrawTextureV(player.bullets[i].texture, player.bullets[i].position, RAYWHITE);
        }
    }
}