#include "RunGame.h"

#include <iostream>

#include "player.h"
#include "raylib.h"

#pragma region delarations

enum Paralax
{
    Background,
    Midground,
    Foreground
};

void ObstacleBehaviour();
void InitPlayerBody();
bool CheckPlaObstCol();
bool RecRecCollision(Rectangle r1, Rectangle r2);
void LoadTextures();
void UpdateBackground();
void BackgroundScrolling(float& scroll, int scrollSpeed, Texture2D texture, Paralax paralax);
void DrawBackground();
void UnloadTextures();
void DrawTextureParalax(Texture2D texture, Rectangle textRectangle, Vector2 pos1, Vector2 pos2, Color color);
Rectangle TextureToRectange(Texture2D texture);
void PrintTexture(Texture2D texture, float scrollSpeed);
void SinusoidalMovement();


static Player player;
static Rectangle obstacle;
float florLevel;

Texture2D background;
Texture2D midground;
Texture2D foreground;

static float scrollingBack = 0.0f;
static float scrollingMid = 0.0f;
static float scrollingFore = 0.0f;
static bool debugMode = false;
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

static constexpr bool fullScreen = true;

void RunGame::Start()
{
    constexpr int width = fullScreen ? 1920 : 720;
    constexpr int height = fullScreen ? 1080 : 480;

    InitWindow(width, height, "Moon Patrol");
    LoadTextures();
    InitPlayerBody();
    florLevel = static_cast<float>(foreground.height) * 0.792f;
    this->version = 0.2;
    obstacle = player.GetBody();
    obstacle.y = static_cast<float>(GetScreenHeight())/2;
}

void LoadTextures()
{
    if (!fullScreen)
    {
        background = LoadTexture("res/pixel_background_2.png");
        foreground = LoadTexture("res/pixel_foreground_2.png");
    }
    else
    {
        background = LoadTexture("res/pixel_background_4.png");
        foreground = LoadTexture("res/pixel_foreground_3.png"); 
    }
    midground = LoadTexture("res/pixel_middleground.png");
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
    obstacle.x -= 100.0f * GetFrameTime();
    if (obstacle.x < 0 - obstacle.width *2)
    {
        obstacle.x = static_cast<float>(GetScreenWidth());
        obstacle.y = static_cast<float>(GetScreenHeight())/2;
    }
        SinusoidalMovement();
}

void SinusoidalMovement()
{
    obstacle.y += sin(obstacle.x/10) * GetFrameTime() * 600.f;
}

void UpdateBackground()
{
    constexpr int scrollSpeed = 10;
    BackgroundScrolling(scrollingFore, scrollSpeed, foreground, Foreground);
    BackgroundScrolling(scrollingMid, scrollSpeed, midground, Midground);
    BackgroundScrolling(scrollingBack, scrollSpeed, background, Background);
}

void BackgroundScrolling(float& scroll, int scrollSpeed, Texture2D texture, Paralax paralax)
{
    const float paralaxSpeed = (paralax != Background ? 5.0f * static_cast<float>(paralax) : 1);
    scroll -= static_cast<float>(scrollSpeed) * GetFrameTime() * paralaxSpeed;
    if (scroll <= -static_cast<float>(texture.width)) scroll = 0;
}

void RunGame::Draw() const
{
    BeginDrawing();

    DrawBackground();
    player.DrawPlayer(); // ??? esta bien esto asi?

    const int florHeight = static_cast<int>(florLevel + player.GetBody().height);
    if (debugMode) DrawLine(0, florHeight, GetScreenWidth(), florHeight, WHITE);


    //TODO DRAW OBSTACLES
    DrawRectangleLinesEx(obstacle, 3, CheckPlaObstCol() ? RED : BLACK);

    PrintTexture(foreground, scrollingFore);

    DrawVersion();
    EndDrawing();
}

void RunGame::DrawVersion() const
{
    const int quarterScreen = GetScreenWidth() / 25;
    DrawText(TextFormat("v%02.01f", version),
             GetScreenWidth() - MeasureText(TextFormat("v %02.01f", version), quarterScreen),
             GetScreenHeight() / 100, quarterScreen, BLACK);
}

void DrawBackground()
{
    ClearBackground(GetColor(0x052c46ff));

    PrintTexture(background, scrollingBack);

    PrintTexture(midground, scrollingMid);
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
    if (player.GetBody().x < 0.f + player.GetBody().x / 2) player.SetX(static_cast<float>(GetScreenWidth()));
    if (player.GetBody().x > static_cast<float>(GetScreenWidth())) player.SetX(0.f);
}

void UnloadTextures()
{
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
}

//DEBERIA PASAR ESTAS FUNCIONES A OTRO ARCHIVO?
void PrintTexture(Texture2D texture, float scrollSpeed)
{
    const Rectangle textureRec = TextureToRectange(texture);
    const Vector2 leftScrolling = {scrollSpeed, 0};
    const Vector2 leftScrolling2 = {textureRec.width + scrollSpeed, 0};

    DrawTextureParalax(texture, textureRec, leftScrolling, leftScrolling2, RAYWHITE);
}

Rectangle TextureToRectange(Texture2D texture)
{
    return {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
}

void DrawTextureParalax(Texture2D texture, Rectangle textRectangle, Vector2 pos1, Vector2 pos2, Color color)
{
    DrawTextureRec(texture, textRectangle, pos1, color);
    DrawTextureRec(texture, textRectangle, pos2, color);
}
