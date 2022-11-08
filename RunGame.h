#pragma once
#include <raylib.h>

class RunGame
{
public:
    RunGame();
    ~RunGame();
private:
    void Start();
    static void PlayerBehaviour();
    static void PlayerGravity();
    static void PlayerControls();
    static void PlayerWarp();
    static void Update();
    void Draw() const;
    void DrawVersion() const;
    static void CheckCollisions();
    double version{};
};
