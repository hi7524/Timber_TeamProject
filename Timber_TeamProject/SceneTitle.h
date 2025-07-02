#pragma once
#include "Scene.h"
#include "TextGo.h"
class SceneTitle : public Scene
{
protected:
	TextGo* title;
	TextGo* teamName;
	TextGo* singlePlay;
	TextGo* multiPlay;

	sf::Sprite SpTitle;
public:
	SceneTitle();

	void ChangeScene();
	void Enter() override;
	void Init() override;
	void Update(float dt) override;
};