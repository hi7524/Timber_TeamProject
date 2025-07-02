#pragma once
#include "Scene.h"

class Player;
class Tree;
class UiHud2;

class SceneDev2 : public Scene
{


public:
	SceneDev2();
	~SceneDev2() override = default;

	void Enter() override;
	void Init() override;
	void Update(float dt) override;
};

