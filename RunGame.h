#pragma once
#include "player.h"

class RunGame
{
public:
    RunGame();
    ~RunGame();
private:
    Player* player{};
    void Start();
    void InitPlayerBody();
    void PlayerBehaviour() const;
    void PlayerGravity() const;
    void PlayerControls() const;
    void PlayerWarp() const;
    void Update() const;
    void Draw() const;
    void DrawVersion() const;
    void CheckCollisions() const;
    double version{};
};
