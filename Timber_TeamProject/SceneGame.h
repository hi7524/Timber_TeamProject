#pragma once
#include "Scene.h"

class Player;
class Tree;
class UiHud;
class Log;

class SceneGame : public Scene
{
protected:
	Player* player;
	Tree* tree;
	UiHud* uiHud;
	Log* log;

	bool isPlaying = false;
	int score = 0;
	float timer = 0.f;
	static float timerMax;

public:
	SceneGame();
	~SceneGame() override;

	static void SetTimerMax(const float& time);
	float GetTimer()const { return timerMax; };
	void Init() override;

	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};

