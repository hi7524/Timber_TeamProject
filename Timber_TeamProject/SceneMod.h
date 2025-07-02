#pragma once
#include "Scene.h"
class SceneMod :public Scene
{
protected:
public:
	SceneMod();

	void Init() override;
	void Update(float dt) override;

};

