#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SceneGame.h"
#include "SceneTitle.h"

class SceneDifficultyManager : public Scene
{
protected:
	TextGo* normal;
	TextGo* hard;

public:
	SceneDifficultyManager();
	~SceneDifficultyManager() override = default;
	void Enter() override;
	void Init() override;
	void Update(float dt) override;
	void Single();
	void Multi();
};


