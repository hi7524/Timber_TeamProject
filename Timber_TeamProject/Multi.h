#pragma once
#include <iostream>
#include "Scene.h"

class Player;
class Tree;
class UiHud2;

class Multi : public Scene
{
protected:
    Player* player1;
    Player* player2;
    Tree* tree1;
    Tree* tree2;
    UiHud2* uiHud2;

    bool isPlaying = true;

    int score1 = 0;
    int score2 = 0;

    float timer = 0.0f;
    static float timerMax;

    // 임시변수! 병합 후 수정할 것
    std::string playMode = "Hard";

public:
    Multi();
    ~Multi() override = default;
    static void SetTimerMax(const float& time);
    void Enter() override;
    void Init() override;
    void Update(float dt) override;
};