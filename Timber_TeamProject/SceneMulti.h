#pragma once
#include <SFML/Audio.hpp>
#include "Scene.h"
#include "SoundGo.h"

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

	SoundGo* chopSound = nullptr;
	SoundGo* deathSound = nullptr;
	SoundGo* timeSound = nullptr;

	sf::Sound sound;
	sf::Music backgroundMusic;

	bool isPlaying = true;
	bool isShowMenu = false;
	bool escape = true;
	bool isMenu = true;
	bool seungYeonCheck = false;

	int score1 = 0;
	int score2 = 0;

	int hp1 = 100;
	int hp2 = 100;


	float timer = 0.0f;
	float timerMax = 5.0f;

public:
    SceneMulti();
	~SceneMulti() override = default;

	void Enter() override;
	void Init() override;
	void Update(float dt) override;
};