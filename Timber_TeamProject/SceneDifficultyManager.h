#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SceneGame.h"
#include "SceneTitle.h"

class SceneDifficultyManager : public Scene
{
protected:
	TextGo* normal = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* hard = new TextGo("fonts/KOMIKAP_.ttf");
	
	
public:
	SceneDifficultyManager();
	~SceneDifficultyManager() override = default;
	void Init() override;
	void Update(float dt) override;
	void Single();
	void Multi();
};


