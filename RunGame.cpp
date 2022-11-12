#include "RunGame.h"

#include <iostream>

#include "Enemy.h"
#include "player.h"
#include "raylib.h"
#include "menu.h"

#pragma region delarations

enum Paralax
{
    Background,
    Midground,
    Foreground
};

void ObstacleBehaviour();
void InitPlayerBody();
bool RecRecCollision(Rectangle r1, Rectangle r2);
void LoadTextures();
void UpdateBackground();
void BackgroundScrolling(float& scroll, int scrollSpeed, Texture2D texture, Paralax paralax);
void DrawBackground();
void UnloadTextures();
void DrawTextureParalax(Texture2D texture, Rectangle textRectangle, Vector2 pos1, Vector2 pos2, Color color);
Rectangle TextureToRectange(Texture2D texture);
void PrintTexture(Texture2D texture, float scrollSpeed);
void UpdateBullets();
void PlayerBullets();
void ObjectDestroyer();

static Bullet bullets[30];
static Enemy enemies[30];
float florLevel;

static Texture2D background;
static Texture2D midground;
static Texture2D foreground;
static Texture2D playerCar;
static Texture2D playerBullet;
static Texture2D enemyBike;

static float scrollingBack = 0.0f;
static float scrollingMid = 0.0f;
static float scrollingFore = 0.0f;

static bool debugMode = false;
extern bool fullscreen;
extern MenuOptions menuOptions;
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
    ObjectDestroyer();
    menuOptions = MenuOptions::menu;
}

RunGame::~RunGame()
{
    std::cout << "Game finished." << std::endl;
}

void RunGame::Start()
{
    LoadTextures();
    InitPlayerBody();
    florLevel = static_cast<float>(foreground.height) * 0.792f;
    this->version = 0.2;
    enemies[0].SetBody({0, florLevel * .97f, player->GetBody().width});
    enemies[0].SetSpeed(static_cast<float>(GetScreenWidth()) / 7.f);
}

void LoadTextures()
{
    if (!fullscreen)
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
    playerCar = LoadTexture("res/entities/player_car.png");
    playerBullet = LoadTexture("res/entities/player_bullet.png");
    enemyBike = LoadTexture("res/entities/enemy_bike.png");
}

void RunGame::InitPlayerBody()
{
    Rectangle playerBody;
    const float initialX = static_cast<float>(GetScreenWidth()) / 2.0f;
    const float initialWidth = static_cast<float>(GetScreenWidth()) / 30.0f;
    const float initialY = static_cast<float>(GetScreenHeight()) / 2.0f;
    const float initialHeight = static_cast<float>(GetScreenHeight()) / 20.0f;
    playerBody.x = initialX;
    playerBody.y = initialY;
    playerBody.width = initialWidth;
    playerBody.height = initialHeight;
    this->player = new Player(playerBody, "santi", initialX);
}

void RunGame::Update() const
{
    PlayerBehaviour();
    UpdateBullets();
    ObstacleBehaviour();
    UpdateBackground();
}

void UpdateBullets()
{
    PlayerBullets();
}

void PlayerBullets()
{
    for (auto& bullet : bullets)
    {
        if (bullet.IsActive())
        {
            bullet.Move();
            bullet.IsOutOfBounds();
        }
    }
}

void ObstacleBehaviour()
{
    enemies[0].MoveRight();
    if (enemies[0].GetBody().x < 0 - enemies[0].GetBody().radius * 2)
    {
        enemies[0].SetX(static_cast<float>(GetScreenWidth()));
        enemies[0].SetY(static_cast<float>(GetScreenHeight()) / 2);
    }
    //TODO WARP ENEMY?
    //enemies[0].SinusoidalMovement();
}

void UpdateBackground()
{
    const int scrollSpeed = GetScreenWidth() / 30;
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
    //TODO Esta bien pasarle la textura por el draw?
    //o es mejor hacer una variable Texture2D?
    //y con los varios enemigos hago un switch para cual textura pasarle?f

    for (auto& enemy : enemies)
    {
        switch (enemy.GetType())
        {
        case Enemy::ground:
            enemies[0].Draw(enemyBike);
            break;
        case Enemy::groundObstacle:
            //enemies[0].Draw(enemyObstacle);
            break;
        case Enemy::air:
            //enemies[0].Draw(enemyHelicopter);
            break;
        case Enemy::airSinusoidal:
            //enemies[0].Draw(enemyHelicopter);
            break;
        default:
            break;
        }
    }
    
    player->Draw(playerCar);
    for (auto& bullet : bullets)
    {
        if (bullet.IsActive())
        {
            bullet.Draw(playerBullet);
        }
    }
    
    const int florHeight = static_cast<int>(florLevel + player->GetBody().height);
    if (debugMode) DrawLine(0, florHeight, GetScreenWidth(), florHeight, WHITE);

    PrintTexture(foreground, scrollingFore);

    DrawVersion();
    EndDrawing();
}

void RunGame::DrawVersion() const
{
    const int fontSize = GetScreenWidth() / 25;
    DrawText(TextFormat("v%02.01f", version),
             GetScreenWidth() - MeasureText(TextFormat("v %02.01f", version), fontSize),
             GetScreenHeight() / 100, fontSize, BLACK);
}

void DrawBackground()
{
    ClearBackground(GetColor(0x052c46ff));

    PrintTexture(background, scrollingBack);

    PrintTexture(midground, scrollingMid);
}

void RunGame::CheckCollisions() const
{
    RecRecCollision(player->GetBody(), {
                        enemies[0].GetBody().x, enemies[0].GetBody().y, enemies[0].GetBody().radius,
                        enemies[0].GetBody().radius
                    });
}

bool RecRecCollision(Rectangle r1, Rectangle r2)
{
    return r1.x + r1.width >= r2.x &&
        r1.x <= r2.x + r2.width &&
        r1.y + r1.height >= r2.y &&
        r1.y <= r2.y + r2.height;
}

void RunGame::PlayerBehaviour() const
{
    PlayerGravity();
    PlayerControls();
    PlayerWarp();
}

void RunGame::PlayerGravity() const
{
    if (player->GetBody().y > florLevel)
    {
        player->SetY(florLevel);
    }
    else
    {
        player->MoveDown();
    }
}

void RunGame::PlayerControls() const
{
    if (IsKeyDown(KEY_D)) player->MoveRight();
    if (IsKeyDown(KEY_A)) player->MoveLeft();
    if (IsKeyReleased(KEY_W)) bullets[0] = player->ShootUp();
    if (IsKeyReleased(KEY_F)) bullets[1] = player->ShootRight();
    player->Jump();
}

void RunGame::PlayerWarp() const
{
    if (player->GetBody().x < 0.f + player->GetBody().x / 2) player->SetX(static_cast<float>(GetScreenWidth()));
    if (player->GetBody().x > static_cast<float>(GetScreenWidth())) player->SetX(0.f);
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

void ObjectDestroyer()
{
}
