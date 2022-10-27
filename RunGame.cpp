#include "RunGame.h"

#include <iostream>

#include "player.h"
#include "raylib.h"

static Player player;

RunGame::RunGame()
{
    InitWindow(720, 480, "MoonLander");
    Start();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
}

RunGame::~RunGame()
{
    std::cout << "Game finished." << std::endl;
}

void RunGame::Start()
{
    Rectangle playerBody;
    playerBody.x = static_cast<float>(GetScreenWidth()) / 2.0f;
    playerBody.y = static_cast<float>(GetScreenHeight()) / 2.0f;
    playerBody.width = static_cast<float>(GetScreenWidth()) / 30.0f;
    playerBody.height = static_cast<float>(GetScreenHeight()) / 20.0f;
    player = {playerBody, "santi", 400.0f};

    this->version = 0.2f;
}

void RunGame::Update()
{
    PlayerControls();
    WarpPlayer();
}

void RunGame::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    player.DrawPlayer(); // ??? esta bien esto asi?
    DrawLine(0, static_cast<int>(GetScreenHeight() / 1.5f + player.GetBody().height), GetScreenWidth(),
             static_cast<int>(GetScreenHeight() / 1.5f + player.GetBody().height), WHITE);
    EndDrawing();
}

void RunGame::DrawVersion() const
{
    DrawText(TextFormat("v %02.01f", version),
             GetScreenWidth() - MeasureText(TextFormat("v %02.01f", version), GetScreenWidth() / 25),
             GetScreenHeight() / 100, GetScreenWidth() / 25, WHITE);
}

void RunGame::CheckCollisions()
{
}

bool RecRecCollision(Rectangle r1, Rectangle r2)
{
    if (r1.x + r1.width >= r2.x && // r1 right edge past r2 left
        r1.x <= r2.x + r2.width && // r1 left edge past r2 right
        r1.y + r1.height >= r2.y && // r1 top edge past r2 bottom
        r1.y <= r2.y + r2.height)
    {
        // r1 bottom edge past r2 top
        return true;
    }
    return false;
}

void RunGame::WarpPlayer()
{
    if (player.GetBody().y > static_cast<float>(GetScreenHeight()) / 1.5f)
    {
        player.SetY(static_cast<float>(GetScreenHeight()) / 1.5f);
    }
    else
    {
        player.MoveDown();
    }
}

void RunGame::PlayerControls()
{
    if (IsKeyDown(KEY_D)) player.MoveRight();
    if (IsKeyDown(KEY_A)) player.MoveLeft();
    if (IsKeyDown(KEY_SPACE)) player.MoveUp();
}
