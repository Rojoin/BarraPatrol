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
    player.x = static_cast<float>(GetScreenWidth())/2.0f;
    player.y = static_cast<float>(GetScreenHeight())/2.0f;
    player.width = static_cast<float>(GetScreenWidth())/30.0f;
    player.height = static_cast<float>(GetScreenHeight())/20.0f;
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
    DrawLine(0, static_cast<int>(GetScreenHeight() / 1.5f+player.height), GetScreenWidth(), static_cast<int>(GetScreenHeight() / 1.5f+player.height), WHITE);
    EndDrawing();
}

void RunGame::WarpPlayer()
{
    if (RunGame::player.y > static_cast<float>(GetScreenHeight()) / 1.5f)
    {
        RunGame::player.y = static_cast<float>(GetScreenHeight()) / 1.5f;
    }
    else
    {
        player.y += GetFrameTime() * 200.0f; 
    }
}

void RunGame::PlayerControls()
{
    if(IsKeyDown(KEY_D)) player.x += GetFrameTime() * 400.0f;
    if(IsKeyDown(KEY_A)) player.x -= GetFrameTime() * 400.0f;
    if(IsKeyDown(KEY_SPACE)) player.y -= GetFrameTime() * 400.0f;
    
}