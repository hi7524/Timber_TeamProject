#pragma once
#include "Scene.h"
#include "SoundGo.h"

class Player;
class Tree;
class UiHud;
class Log;
class UiHud2;
class SetTing;
class UiMenu;

class SceneGame : public Scene
{
protected:
	Player* player;
	Tree* tree;
	UiHud* uiHud;
	Log* log;
	UiHud2* uiHud2;
	SetTing* setTing;
	UiMenu* uiMenu;

	SoundGo* chopSound = nullptr;
	SoundGo* deathSound = nullptr;
	SoundGo* timeSound = nullptr;

	sf::Sound sound;

	bool isShowMenu = false;
	bool isPlaying = false;
	bool isMenu = true;
	bool escape = false;
	

	int score = 0;
	float timer = 0.f;
	static float timerMax;

public:
	SceneGame();
	~SceneGame() override;

	void SetIsShowMenu(bool show) { isShowMenu = show; }
	static void SetTimerMax(const float& time);
	float GetTimer()const { return timerMax; };
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};

