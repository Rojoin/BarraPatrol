#pragma once
#include "Enemy.h"
#include "player.h"

class RunGame
{
public:
    RunGame();
    ~RunGame();
private:
    void Start();
    void InitPlayerBody();
    void PlayerBehaviour();
    void PlayerGravity() const;
    void PlayerControls();
    void PlayerWarp() const;
    void Update();
    void Draw() const;
    void DrawVersion() const;
    void CheckCollisions() const;
    void PlayerBullets();
    void ObstacleBehaviour();
    void UpdateBullets();
    
    double version{};
    Player* player{};
    Bullet bullets[30];
    Enemy enemies[30];
};
