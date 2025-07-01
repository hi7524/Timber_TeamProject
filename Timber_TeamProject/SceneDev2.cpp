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
	// ���ҽ� ID ����
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/cloud.png");
	texIds.push_back("graphics/bee.png");
	texIds.push_back("graphics/tree.png");
	texIds.push_back("graphics/branch.png");
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/axe.png");
	texIds.push_back("graphics/rip.png");

	fontIds.push_back("fonts/KOMIKAP_.ttf");

	// ������Ʈ �߰� (��� ���)
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

	// ������Ʈ �߰� (���� ���)
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

	// �÷��� ��忡 ���� ����
	if (playMode == "Normal")
	{
		timerMax = 5.0f; // 5��
	}
	else if (playMode == "Hard")
	{
		timerMax = 3.0f; // 3��
	}

	// ���� ��ġ ����
	sf::Vector2f windowW = FRAMEWORK.GetWindowSizeF();
	float treeOffset = 400.0f;
	
	sf::Vector2f tree1Pos = { windowW.x * 0.5f - treeOffset, 0.0f };
	sf::Vector2f tree2Pos = { windowW.x * 0.5f + treeOffset, 0.0f };

	tree1->SetPosition(tree1Pos);
	tree2->SetPosition(tree2Pos);

	// �÷��̾� ��ġ ����
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

		// �÷��̾� 1 ����
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Left);

			// �׽�Ʈ �ڵ�
			score1 += 10;
			uiHud2->SetScore(score1, 1);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Right);
		}


		// �÷��̾� 2 ����
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Left);
			
			// �׽�Ʈ �ڵ�
			score2 += 10;
			uiHud2->SetScore(score2, 2);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Right);
		}

		// �浹 üũ

		// �� ���� ���� �׾ �̱�
		// �ð��� ������ �������� ������ �� ���� ���� �̱�
	}
}