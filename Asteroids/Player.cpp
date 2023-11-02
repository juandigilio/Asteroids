#include "Player.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>


using namespace Globals;


void LoadPlayer(Player& player)
{
    player.texture = LoadTexture("Assets/Images/ship.png");
    player.position.x = screenCenter.x - player.texture.width / 2;
    player.position.y = screenCenter.y - player.texture.height / 2;
    player.radius = player.texture.width / 2.0f;
    player.source = { 0, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
    player.totalPoints = 0;
    player.availableLives = 3;

    player.shoot = LoadSound("Assets/Sounds/shoot.wav");
    player.thousand = LoadSound("Assets/Sounds/crash.wav");


    for (int i = 0; i < maxBulletsQnty; i++)
    {
        player.bullets[i].texture = LoadTexture("Assets/Images/bullet.png");
        player.bullets[i].isAlive = false;
        player.bullets[i].radius = player.bullets[i].texture.width / 2.0f;
        player.bullets[i].source = { 0, 0, static_cast<float>(player.bullets[i].texture.width), static_cast<float>(player.bullets[i].texture.height) };
    }
}

static void Shoot(Player& player)
{
    for (int i = 0; i < maxBulletsQnty; i++)
    {
        if (!player.bullets[i].isAlive)
        {
            player.bullets[i].position = player.GetCenter();
            player.bullets[i].rotation = player.rotation;
            player.bullets[i].isAlive = true;
            player.bullets[i].firstCrossing = true;

            player.bullets[i].direction = Vector2Subtract(GetMousePosition(), player.bullets[i].position);
            float length = Vector2Length(player.bullets[i].direction);

            player.bullets[i].direction = Vector2Divide(player.bullets[i].direction, { length, length });

            PlaySound(player.shoot);

            break;
        }
    }
}

static void MovePlayer(Player& player)
{
    player.velocity = Vector2Scale(player.direction, player.speed * GetFrameTime());
    player.position = Vector2Add(player.position, player.velocity);

    if (player.position.x > screenWidth + player.texture.width / 2.0f)
    {
        player.position.x = (-player.texture.width / 2.0f);
        player.position.y = screenHeight - player.position.y;
    }
    else if (player.position.x < 0.0f - player.texture.width / 2.0f)
    {
        player.position.x = screenWidth + (player.texture.width / 2.0f);
        player.position.y = screenHeight - player.position.y;
    }
    else if (player.position.y > screenHeight + player.texture.height / 2.0f)
    {
        player.position.x = screenWidth - player.position.x;
        player.position.y = (-player.texture.height / 2.0f);
    }
    else if (player.position.y < 0.0f - player.texture.height / 2.0f)
    {
        player.position.x = screenWidth - player.position.x;
        player.position.y = screenHeight + (player.texture.height / 2.0f);
    }
}

static void MoveBullets(Bullet& bullet)
{
    bullet.velocity = Vector2Scale(bullet.direction, bullet.speed * GetFrameTime());
    bullet.position = Vector2Add(bullet.position, bullet.velocity);

    if (bullet.position.x > screenWidth + bullet.texture.width / 2.0f)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = (-bullet.texture.width / 2.0f);
            bullet.position.y = screenHeight - bullet.position.y;
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
            bullet.firstCrossing = true;
        }
    }
    else if (bullet.position.x < 0.0f - bullet.texture.width / 2.0f)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = screenWidth + (bullet.texture.width / 2.0f);
            bullet.position.y = screenHeight - bullet.position.y;
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
        }
    }
    else if (bullet.position.y > screenHeight + bullet.texture.height / 2.0f)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = screenWidth - bullet.position.x;
            bullet.position.y = (-bullet.texture.height / 2.0f);
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
        }
    }
    else if (bullet.position.y < 0.0f - bullet.texture.height / 2.0f)
    {
        if (bullet.firstCrossing)
        {
            bullet.position.x = screenWidth - bullet.position.x;
            bullet.position.y = screenHeight + (bullet.texture.height / 2.0f);
            bullet.firstCrossing = false;
        }
        else
        {
            bullet.isAlive = false;
        }
    }
}

void GetPlayerInput(Player& player, GameSceen& currentSceen)
{
    player.rotation = static_cast<float>(atan2(static_cast<double>(GetMousePosition().y - static_cast<double>(player.texture.height / 2.0f)) - player.position.y, static_cast<double>(GetMousePosition().x - static_cast<double>(player.texture.width / 2.0f)) - player.position.x)) * RAD2DEG + 90.0f;

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        player.speed += 0.05f;

        if (player.speed >= player.maxSpeed)
        {
            player.speed = player.maxSpeed;
        }

        Vector2 targetDirection = Vector2Subtract(GetMousePosition(), player.position);
        float targetLength = Vector2Length(targetDirection);

        targetDirection = Vector2Divide(targetDirection, { targetLength, targetLength });

        player.direction = Vector2Lerp(player.direction, targetDirection, interpolationFactor * GetFrameTime());

        float length = Vector2Length(player.direction);

        if (length > 0.1)
        {
            player.direction = Vector2Divide(player.direction, { length, length });
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Shoot(player);
    }

    if (IsKeyDown(KEY_ESCAPE))
    {
        currentSceen = GameSceen::PAUSE;
    }
}

void UpdatePlayer(Player& player)
{
    if (player.totalPoints >= player.thousandCouner + 1000)
    {
        PlaySound(player.thousand);

        player.thousandCouner += 1000;
    }

    MovePlayer(player);

    for (int i = 0; i < maxBulletsQnty; i++)
    {
        if (player.bullets[i].isAlive)
        {
            MoveBullets(player.bullets[i]);
        }
    }
}

void DrawPlayer(Player& player)
{
    Rectangle dest = { player.GetCenter().x, player.GetCenter().y, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
    Vector2 origin = { static_cast<float>(player.texture.width / 2), static_cast<float>(player.texture.height / 2) };

    DrawTexturePro(player.texture, player.source, dest, origin, player.rotation + 90.0f, RAYWHITE);



    for (int i = 0; i < maxBulletsQnty; i++)
    {
        if (player.bullets[i].isAlive)
        {
            dest = { player.bullets[i].GetCenter().x, player.bullets[i].GetCenter().y, static_cast<float>(player.bullets[i].texture.width), static_cast<float>(player.bullets[i].texture.height) };
            origin = { static_cast<float>(player.bullets[i].texture.width / 2), static_cast<float>(player.bullets[i].texture.height / 2) };

            DrawTexturePro(player.bullets[i].texture, player.bullets[i].source, dest, origin, player.bullets[i].rotation - 90, RAYWHITE);
        }
    }
}