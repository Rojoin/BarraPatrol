#include "RunGame.h"

#include <iostream>

#include "player.h"
#include "raylib.h"

#pragma region delarations
void ObstacleBehaviour();
void InitPlayerBody();
bool CheckPlaObstCol();
bool RecRecCollision(Rectangle r1, Rectangle r2);
void LoadTextures();
void UpdateBackground();
void DrawBackground();
void UnloadTextures();


static Player player;
static Rectangle obstacle;
float florLevel;

Texture2D background;
Texture2D midground;
Texture2D foreground;

static float scrollingBack = 0.0f;
static float scrollingMid = 0.0f;
static float scrollingFore = 0.0f;
#pragma endregion

RunGame::RunGame()
{
    Start();
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
    UnloadTextures();
}

RunGame::~RunGame()
{
    std::cout << "Game finished." << std::endl;
}

void RunGame::Start()
{
    InitWindow(720, 480, "Moon Patrol");
    LoadTextures();
    InitPlayerBody();
    florLevel =  (float)foreground.height* 0.792f;
    this->version = 0.1f;
    obstacle = {
        static_cast<float>(GetScreenWidth()) * 0.75f, florLevel, player.GetBody().width, player.GetBody().height
    };
}

void LoadTextures() 
{
    background = LoadTexture("res/pixel_background2.png");
    midground = LoadTexture("res/pixel_middleground.png");
    foreground = LoadTexture("res/pixel_foreground2.png");
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

void RunGame::Update()
{
    PlayerBehaviour();
    ObstacleBehaviour();
    UpdateBackground();
}

//TODO CREATE OBSTACLE OBJECT
void ObstacleBehaviour()
{
    obstacle.x -= 145.0f * GetFrameTime();
    if (obstacle.x < 0 - obstacle.width / 3) obstacle.x = static_cast<float>(GetScreenWidth());
}

void UpdateBackground()
{
    int backgroundSpeed = 5;
    scrollingBack -= backgroundSpeed * GetFrameTime();
    scrollingMid -= backgroundSpeed * 5.f * GetFrameTime();
    scrollingFore -= backgroundSpeed * 10.f * GetFrameTime();

    if (scrollingBack <= -background.width) scrollingBack = 0;
    if (scrollingMid <= -midground.width) scrollingMid = 0;
    if (scrollingFore <= -foreground.width) scrollingFore = 0;
}

void RunGame::Draw() const
{
    BeginDrawing();
    DrawBackground();
    player.DrawPlayer(); // ??? esta bien esto asi?
    //DrawLine(0, static_cast<int>(florLevel + player.GetBody().height), GetScreenWidth(),
             //static_cast<int>(florLevel + player.GetBody().height), WHITE);
    DrawRectangleLinesEx(obstacle, 3, CheckPlaObstCol() ? RED : WHITE);
    DrawVersion();
    EndDrawing();
}

void RunGame::DrawVersion() const
{
    DrawText(TextFormat("v%02.01f", version),
             GetScreenWidth() - MeasureText(TextFormat("v %02.01f", version), GetScreenWidth() / 25),
             GetScreenHeight() / 100, GetScreenWidth() / 25, WHITE);
}
void DrawBackground()
{
    ClearBackground(GetColor(0x052c46ff));
    Vector2 scrolling = { scrollingBack, 0 };
    Vector2 scrolling2 = { background.width + scrollingBack, 0 };
    DrawTextureRec(background, { 0, 0, (float)background.width, (float)background.height }, scrolling, RAYWHITE);
    DrawTextureRec(background, { 0, 0, (float)background.width, (float)background.height }, scrolling2, RAYWHITE);

    Vector2 midgroundImage = { scrollingMid, -(float)GetScreenHeight() / 6.5f };
    Vector2 midgroundImage2 = { midground.width + scrollingMid, -(float)GetScreenHeight() / 6.5f };
    DrawTextureRec(midground, { 0, 0, (float)midground.width, (float)midground.height }, midgroundImage, RAYWHITE);
    DrawTextureRec(midground, { 0, 0, (float)midground.width, (float)midground.height }, midgroundImage2, RAYWHITE);

    Vector2 foregroundImage = { scrollingFore, (float)(GetScreenHeight() - foreground.height) };
    Vector2 foregroundImage2 = { foreground.width + scrollingFore, (float)(GetScreenHeight() - foreground.height) };
    DrawTextureRec(foreground, { 0, 0, (float)foreground.width, (float)foreground.height }, foregroundImage, RAYWHITE);
    DrawTextureRec(foreground, { 0, 0, (float)foreground.width, (float)foreground.height }, foregroundImage2, RAYWHITE);
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
    return r1.x + r1.width >= r2.x &&
        r1.x <= r2.x + r2.width &&
        r1.y + r1.height >= r2.y &&
        r1.y <= r2.y + r2.height;
}

void RunGame::PlayerBehaviour()
{
    PlayerGravity();
    PlayerControls();
    PlayerWarp();
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
    player.Jump();
}

void RunGame::PlayerWarp() 
{
    if (player.GetBody().x < 0.f + player.GetBody().x/2) player.SetX((float)GetScreenWidth());
    if (player.GetBody().x > (float)GetScreenWidth()) player.SetX(0.f);
}

void UnloadTextures() 
{
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
}