#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "Single.h"

void SceneMgr::Init()
{
	scenes.push_back(new SceneTitle());
	scenes.push_back(new Single());
	scenes.push_back(new SceneTitle());
	scenes.push_back(new SceneGame());
	scenes.push_back(new SceneDev1());
	scenes.push_back(new SceneDev2());

	for (auto scene : scenes)
	{
		if ((int)scene->Id == (int)startScene)
		{
			scene->Init();
			scene->Enter();
		}
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (scene->Id == currentScene)
		{
			scene->Exit();
		}
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[(int)currentScene]->Init();
		scenes[(int)currentScene]->Enter();
	}

	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}