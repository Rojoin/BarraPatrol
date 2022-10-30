#include "RunGame.h"

#include <iostream>

#include "player.h"
#include "raylib.h"

bool RecRecCollision(Rectangle r1, Rectangle r2);
void InitPlayerBody();
bool CheckPlaObstCol();
static Player player;
static Rectangle obstacle;
float florLevel;

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
    InitPlayerBody();
    florLevel =static_cast<float>(GetScreenHeight()) / 1.5f;
        this->version = 0.2f;
    obstacle = {static_cast<float>(GetScreenWidth()) * 0.75f, static_cast<float>(GetScreenHeight()) / 1.5f, player.GetBody().width, player.GetBody().height};
}

void InitPlayerBody()
{
    Rectangle playerBody;
    playerBody.x = static_cast<float>(GetScreenWidth()) / 2.0f;
    playerBody.y = static_cast<float>(GetScreenHeight()) / 2.0f;
    playerBody.width = static_cast<float>(GetScreenWidth()) / 30.0f;
    playerBody.height = static_cast<float>(GetScreenHeight()) / 20.0f;
    player = {playerBody, "santi", 400.0f};
}
static int counter = 0;
void RunGame::Update()
{
    PlayerControls();
    PlayerGravity();
    if(player.GetBody().y > florLevel) counter++;
    obstacle.x -= 200.0f * GetFrameTime();
    if (obstacle.x< 0 -obstacle.width/3) obstacle.x = static_cast<float>(GetScreenWidth());
}

void RunGame::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    player.DrawPlayer(); // ??? esta bien esto asi?
    DrawLine(0, static_cast<int>(florLevel + player.GetBody().height), GetScreenWidth(), static_cast<int>(florLevel + player.GetBody().height), WHITE);
    DrawRectangleLinesEx(obstacle, 3, CheckPlaObstCol() ? RED : WHITE);

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

bool CheckPlaObstCol()
{
    return RecRecCollision(player.GetBody(), obstacle);
}

bool RecRecCollision(Rectangle r1, Rectangle r2)
{
    if (r1.x + r1.width >= r2.x && 
        r1.x <= r2.x + r2.width && 
        r1.y + r1.height >= r2.y &&
        r1.y <= r2.y + r2.height)
    {
        return true;
    }
    return false;
}

void RunGame::PlayerGravity()
{
    if (player.GetBody().y > florLevel)
    {
        player.SetY(florLevel);
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
