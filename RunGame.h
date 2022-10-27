#pragma once
#include <raylib.h>

class RunGame
{
public:
    RunGame();
    ~RunGame();
private:
    void Start();
    static void WarpPlayer();
    static void PlayerControls();
    static void Update();
    static void Draw();
    void DrawVersion() const;
    static void CheckCollisions();
    float version{};
};
