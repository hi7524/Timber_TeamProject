#pragma once
#include "Scene.h"
class Multi :public Scene
{
protected:
public:
	Multi();

	void ChangeScene();
	void Init() override;
	void Update(float dt) override;
};

