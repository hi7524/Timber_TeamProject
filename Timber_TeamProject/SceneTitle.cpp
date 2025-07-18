#include "stdafx.h"
#include "SceneTitle.h"
#include "TextGo.h"
#include "SpriteGo.h"

SceneTitle::SceneTitle() : Scene(SceneIds::Title)
{
}

void SceneTitle::Enter()
{
	
	AddGameObject(new SpriteGo("graphics/Title.png"));
	title = (TextGo*)(AddGameObject(new TextGo("fonts/KOMIKAP_.ttf")));
	singlePlay = (TextGo*)(AddGameObject(new TextGo("fonts/KOMIKAP_.ttf")));
	multiPlay = (TextGo*)(AddGameObject(new TextGo("fonts/KOMIKAP_.ttf")));
	
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	sf::Vector2f titlePos = { bounds.width * 0.2f,bounds.height * 0.1f };
	sf::Vector2f teamNamePos = { bounds.width * 0.8f,bounds.height * 0.3f };
	sf::Vector2f singlePlayPos = { bounds.width * 0.2f,bounds.height * 0.8f };
	sf::Vector2f multiPlayPos = { bounds.width * 0.8f,bounds.height * 0.8f };

	title->SetString("TIMBER");
	title->SetCharacterSize(200);
	title->SetFillColor(sf::Color::Black);
	title->SetOrigin(Origins::MC);
	title->SetPosition(titlePos);

	singlePlay->SetString("SinglePlay");
	singlePlay->SetCharacterSize(100);
	singlePlay->SetFillColor(sf::Color::Black);
	singlePlay->SetOrigin(Origins::MC);
	singlePlay->SetPosition(singlePlayPos);

	multiPlay->SetString("MultiPlay");
	multiPlay->SetCharacterSize(100);
	multiPlay->SetFillColor(sf::Color::Black);
	multiPlay->SetOrigin(Origins::MC);
	multiPlay->SetPosition(multiPlayPos);

	Scene::Enter();
}

void SceneTitle::Init()
{
	fontIds.push_back("fonts/KOMIKAP_.ttf");
	texIds.push_back("graphics/Title.png");

	Scene::Init();
}

void SceneTitle::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		singlePlay->SetFillColor(sf::Color::Red);
		multiPlay->SetFillColor(sf::Color::Black);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		multiPlay->SetFillColor(sf::Color::Red);
		singlePlay->SetFillColor(sf::Color::Black);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		if (singlePlay->GetFillColor() == sf::Color::Red)
		{
			SCENE_MGR.ChangeScene(SceneIds::Single);
		}
		else if (multiPlay->GetFillColor() == sf::Color::Red)
		{
			SCENE_MGR.ChangeScene(SceneIds::CharChoiceMulti);
		}
	}
}