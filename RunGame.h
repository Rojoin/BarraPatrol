#pragma once
#include <raylib.h>

class RunGame
{
public:
    RunGame();
    ~RunGame();
private:
    void Start();
    void WarpPlayer();
    void PlayerControls();
    void Update();
    void Draw();
    
    Rectangle player;

};
