#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "BackgroundElement.h"
#include "Tree.h"
#include "Player.h"
#include "UiHud2.h"


SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	// 리소스 ID 설정
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/cloud.png");
	texIds.push_back("graphics/bee.png");
	texIds.push_back("graphics/tree.png");
	texIds.push_back("graphics/branch.png");
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/axe.png");
	texIds.push_back("graphics/rip.png");

	fontIds.push_back("fonts/KOMIKAP_.ttf");

	// 오브젝트 추가 (배경 요소)
	AddGameObject(new SpriteGo("graphics/background.png"));

	for (int i = 0; i < 3; ++i)
	{
		BackgroundElement* element = (BackgroundElement*)AddGameObject(
			new BackgroundElement("graphics/cloud.png"));
	}

	BackgroundElement* element = (BackgroundElement*)AddGameObject(new BackgroundElement("graphics/bee.png"));
	element->minScale = 1.f;
	element->maxScale = 1.f;
	element->minY = 600;
	element->maxY = 800;
	element->minSpeed = 400;
	element->maxSpeed = 600;
	element->SetMoveType(BackgroundElement::MoveType::Wave);

	// 오브젝트 추가 (게임 요소)
	tree1 = (Tree*)AddGameObject(new Tree());
	tree2= (Tree*)AddGameObject(new Tree());

	player1 = (Player*)AddGameObject(new Player());
	player2 = (Player*)AddGameObject(new Player());

	uiHud2 = (UiHud2*)AddGameObject(new UiHud2());

	Scene::Init();
}

void SceneDev2::Enter()
{
	Scene::Enter();

	// 플레이 모드에 따른 설정
	if (playMode == "Normal")
	{
		timerMax = 5.0f; // 5초
	}
	else if (playMode == "Hard")
	{
		timerMax = 3.0f; // 3초
	}

	// 나무 위치 설정
	sf::Vector2f windowW = FRAMEWORK.GetWindowSizeF();
	float treeOffset = 400.0f;
	
	sf::Vector2f tree1Pos = { windowW.x * 0.5f - treeOffset, 0.0f };
	sf::Vector2f tree2Pos = { windowW.x * 0.5f + treeOffset, 0.0f };

	tree1->SetPosition(tree1Pos);
	tree2->SetPosition(tree2Pos);

	// 플레이어 위치 설정
	sf::Vector2f player1Pos = tree1->GetPosition();
	player1Pos.y = 950.0f;
	sf::Vector2f player2Pos = tree2->GetPosition();
	player2Pos.y = 950.0f;

	player1->SetPosition(player1Pos);
	player2->SetPosition(player2Pos);

	// UI
	timer = timerMax;
	//uiHud2->SetTimeBar(timer / timerMax);
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (isPlaying)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			//SCENE_MGR.ChangeScene(SceneIds::Dev1);
		}

		// 플레이어 1 조작
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Left);

			// 테스트 코드
			score1 += 10;
			uiHud2->SetScore(score1, 1);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Right);
		}


		// 플레이어 2 조작
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Left);
			
			// 테스트 코드
			score2 += 10;
			uiHud2->SetScore(score2, 2);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Right);
		}

		// 충돌 체크

		// 한 쪽이 먼저 죽어도 이김
		// 시간이 끝까지 갔을때는 점수가 더 높은 쪽이 이김
	}
}