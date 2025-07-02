#include "stdafx.h"
#include "SceneDifficultyManager.h"
#include "SpriteGo.h"
#include "SceneGame.h"
SceneDifficultyManager::SceneDifficultyManager()
	:Scene(SceneIds::Difficulty)
{
}

void SceneDifficultyManager::Enter()
{
	AddGameObject(new SpriteGo("graphics/Title.png"));
	normal = (TextGo*)(AddGameObject(new TextGo("fonts/KOMIKAP_.ttf")));
	hard = (TextGo*)(AddGameObject(new TextGo("fonts/KOMIKAP_.ttf")));

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	sf::Vector2f normalPos = { bounds.width * 0.2f,bounds.height * 0.5f };
	sf::Vector2f hardPos = { bounds.width * 0.8f,bounds.height * 0.5f };

	normal->SetString("Normal");
	normal->SetCharacterSize(100);
	normal->SetFillColor(sf::Color::Black);
	normal->SetOrigin(Origins::MC);
	normal->SetPosition(normalPos);

	hard->SetString("Hard");
	hard->SetCharacterSize(100);
	hard->SetFillColor(sf::Color::Black);
	hard->SetOrigin(Origins::MC);
	hard->SetPosition(hardPos);
	Scene::Enter();
}

void SceneDifficultyManager::Init()
{
	fontIds.push_back("fonts/KOMIKAP_.ttf");
	texIds.push_back("graphics/Title.png");

	Scene::Init();
}

void SceneDifficultyManager::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		normal->SetFillColor(sf::Color::Red);
		hard->SetFillColor(sf::Color::Black);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		hard->SetFillColor(sf::Color::Red);
		normal->SetFillColor(sf::Color::Black);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		if (normal->GetFillColor() == sf::Color::Red)
		{
			SceneGame::SetTimerMax(5.0f);
			SCENE_MGR.ChangeScene(SceneIds::Game);

		}
		else if (hard->GetFillColor() == sf::Color::Red)
		{
			SceneGame::SetTimerMax(2.0f);
			SCENE_MGR.ChangeScene(SceneIds::Game);

		}
		
	}
}

