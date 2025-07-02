#include "stdafx.h"
#include "SceneMulti.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "BackgroundElement.h"
#include "Tree.h"
#include "Player.h"
#include "UiHud2.h"


SceneMulti::SceneMulti()
	: Scene(SceneIds::Multi)
{
}

void SceneMulti::Init()
{
	// ���ҽ� ID ����
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/cloud.png");
	texIds.push_back("graphics/bee.png");
	texIds.push_back("graphics/tree.png");
	texIds.push_back("graphics/branch.png");
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/player1.png");
	texIds.push_back("graphics/player2.png");
	texIds.push_back("graphics/axe.png");
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
	tree2 = (Tree*)AddGameObject(new Tree());

	player1 = (Player*)AddGameObject(new Player(SCENE_MGR.selectedPlayer1));
	player2 = (Player*)AddGameObject(new Player(SCENE_MGR.selectedPlayer2));

	uiHud2 = (UiHud2*)AddGameObject(new UiHud2());

	Scene::Init();
}

void SceneMulti::Enter()
{
	Scene::Enter();


	timerMax = 5.0f; // 5��



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
	uiHud2->SetTimeBar(timer / timerMax);
}

void SceneMulti::Update(float dt)
{
	Scene::Update(dt);

	// �Ͻ����� �� �簳
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		isPlaying = !isPlaying;

		if (timer <= 0)
		{
			timer = timerMax;
		}
		else
		{
			if (isPlaying)
			{
				uiHud2->SetShowTitle(false);
				uiHud2->SetShowDetail(false);
			}
			else
			{
				uiHud2->SetTitleMessage("Pause");
				uiHud2->SetDetailMessage("Press Enter Key to Restart");
				uiHud2->SetShowTitle(true);
				uiHud2->SetShowDetail(true);
			}
		}
	}

	if (isPlaying)
	{
		// �÷���
		FRAMEWORK.SetTimeScale(1);
		timer -= dt;

		// Ÿ�̸�
		uiHud2->SetTimeBar(timer / timerMax);

		// ���ѽð� ���� ��
		if (timer <= 0)
		{
			timer = 0;
			isPlaying = false;

			// ������ ���� ��� ���
			if (score1 > score2)
			{
				uiHud2->SetTitleMessage("Player 1 Winner!");
				uiHud2->SetDetailMessage("1st Player 1: " + std::to_string(score1) + "\n2nd Player 2: " + std::to_string(score2));
			}
			else if (score1 < score2)
			{
				uiHud2->SetTitleMessage("Player 2 Winner!");
				uiHud2->SetDetailMessage("1st Player 2: " + std::to_string(score2) + "\n2nd Player 1: " + std::to_string(score1));
			}
			else
			{
				uiHud2->SetTitleMessage("Draw!");
			}

			uiHud2->SetShowTitle(true);
			uiHud2->SetShowDetail(true);
		}
		else
		{
			uiHud2->SetShowTitle(false);
			uiHud2->SetShowDetail(false);
		}


		// �÷��̾� 1 ����
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Left);
			player1->SetDrawAxe(true);

			// �浹 üũ
			if (tree1->GetSide() == player1->GetSide())
			{
				score1 -= 20;
				if (score1 <= 0)
				{
					score1 = 0;
				}
			}
			else
			{
				score1 += 10;
			}

			// Score UI ������Ʈ
			uiHud2->SetScore(score1, 1);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Right);
			player1->SetDrawAxe(true);

			// �浹 üũ
			if (tree1->GetSide() == player1->GetSide())
			{
				score1 -= 20;
				if (score1 <= 0)
				{
					score1 = 0;
				}
			}
			else
			{
				score1 += 10;
			}
			// Score UI ������Ʈ
			uiHud2->SetScore(score1, 1);
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::A) || InputMgr::GetKeyUp(sf::Keyboard::D))
		{
			player1->SetDrawAxe(false);
		}

		// �÷��̾� 2 ����
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Left);
			player2->SetDrawAxe(true);

			// �浹 üũ
			if (tree2->GetSide() == player2->GetSide())
			{
				score2 -= 20;
				if (score2 <= 0)
				{
					score2 = 0;
				}
			}
			else
			{
				score2 += 10;
			}

			// Score UI ������Ʈ
			uiHud2->SetScore(score2, 2);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Right);
			player2->SetDrawAxe(true);

			// �浹 üũ
			if (tree2->GetSide() == player2->GetSide())
			{
				score2 -= 20;
				if (score2 <= 0)
				{
					score2 = 0;
				}
			}
			else
			{
				score2 += 10;
			}

			// Score UI ������Ʈ
			uiHud2->SetScore(score2, 2);
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			player2->SetDrawAxe(false);
		}
	}
	else
	{
		// �÷��� ����
		FRAMEWORK.SetTimeScale(0);
	}
}
