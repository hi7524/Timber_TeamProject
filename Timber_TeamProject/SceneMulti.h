#pragma once
#include "Scene.h"

class Player;
class Tree;
class UiHud2;
class UiMenu;
class SceneMulti : public Scene
{
protected:
	Player* player1;
	Player* player2;
	Tree* tree1;
	Tree* tree2;
	UiHud2* uiHud2;
	UiMenu* uiMenu;

	bool isPlaying = true;
	bool isShowMenu = false;

	bool isMenu = true;

	int score1 = 0;
	int score2 = 0;

	float timer = 0.0f;
	float timerMax = 5.0f;

public:
    SceneMulti();
	~SceneMulti() override = default;

	void Enter() override;
	void Init() override;
	void Update(float dt) override;
};