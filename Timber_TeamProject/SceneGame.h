#pragma once
#include "Scene.h"
#include "SoundGo.h"

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

	SoundGo* chopSound = nullptr;
	SoundGo* deathSound = nullptr;
	SoundGo* timeSound = nullptr;

	sf::Sound sound;

	bool isPlaying = false;
	int score = 0;
	float timer = 0.f;
	float timerMax = 5.f;

public:
	SceneGame();
	~SceneGame() override;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};

