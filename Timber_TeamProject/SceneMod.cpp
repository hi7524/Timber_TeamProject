#include "stdafx.h"
#include "SceneMod.h"
#include "TextGo.h"

SceneMod::SceneMod()
	: Scene(SceneIds::SelectMod)
{
}

void SceneMod::Init()
{
	fontIds.push_back("fonts/KOMIKAP_.ttf");

	TextGo* go = new TextGo("fonts/KOMIKAP_.ttf");
	go->SetString("SelectMod");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	AddGameObject(go);

	Scene::Init();
}

void SceneMod::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}
}


