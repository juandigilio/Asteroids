#pragma once

#include "GameData.h"

const int maxBulletsQnty = 30;

struct Bullet
{
    Vector2 position{};
    Vector2 velocity{};
    Vector2 direction{};
    float rotation{};
    float radius{};
    float speed = 360.0f;
    bool firstCrossing = true;
    bool isAlive = false;
    Texture2D texture{};
    Rectangle source{};

    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
    }
};

struct Player
{
    Vector2 position{};
	Vector2 velocity{};
	Vector2 direction{};
	float speed = 0.0f;
    float maxSpeed = 120.0f;
	float rotation = 0.0f;
    float targetRotation{};
    float radius{};
	int totalPoints = 0;
	int availableLives = 3;
    bool isColliding = false;
    float lastCollide = 0.0f;
    bool isAlive = true;
	Texture2D texture{};
    Rectangle source{};

    Bullet bullets[maxBulletsQnty]{};

    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
    }
};

void LoadPlayer(Player& player);

void GetPlayerInput(Player& player, GameSceen& currentSceen);

void UpdatePlayer(Player& player);

void DrawPlayer(Player& player);
