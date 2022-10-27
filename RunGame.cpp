#include "RunGame.h"

#include <iostream>

#include "raylib.h"


RunGame::RunGame()
{
    InitWindow(720, 480, "MoonLander");
    player={};
    Start();
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
}

RunGame::~RunGame()
{
    std::cout << "Game finished."<<std::endl;
}

void RunGame::Start()
{
    RunGame::player.x = static_cast<float>(GetScreenWidth())/2.0f;
    RunGame::player.y = static_cast<float>(GetScreenHeight())/2.0f;
    RunGame::player.width = static_cast<float>(GetScreenWidth())/30.0f;
    RunGame::player.height = static_cast<float>(GetScreenHeight())/20.0f;
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
    DrawRectangleRec(RunGame::player, WHITE);
    EndDrawing();
}

void RunGame::WarpPlayer()
{
    if (RunGame::player.y > static_cast<float>(GetScreenHeight()) / 1.5f)
    {
        RunGame::player.y = static_cast<float>(GetScreenHeight()) / 1.5f;
    }
}

void RunGame::PlayerControls()
{
    if(IsKeyPressed('d'))
    {
        RunGame::player.x += GetFrameTime() * 40;        
    }
}