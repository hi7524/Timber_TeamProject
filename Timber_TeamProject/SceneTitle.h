#pragma once
#include "Scene.h"
#include "TextGo.h"
class SceneTitle : public Scene
{
protected:
	TextGo* title = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* teamName = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* singlePlay = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* multiPlay = new TextGo("fonts/KOMIKAP_.ttf");
	

public:
	SceneTitle();

	void ChangeScene();
	
	void Init() override;
	void Update(float dt) override;
};