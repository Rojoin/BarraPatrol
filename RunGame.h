#pragma once
#include <raylib.h>

class RunGame
{
public:
    RunGame();
    ~RunGame();
private:
    void Start();
    static void PlayerGravity();
    static void PlayerControls();
    static void Update();
    void Draw() const;
    void DrawVersion() const;
    void CheckCollisions();
    float version{};
};
