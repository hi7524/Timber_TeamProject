#include "stdafx.h"
#include "SceneMulti.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"
#include "BackgroundElement.h"
#include "Tree.h"
#include "Player.h"
#include "UiHud2.h"
#include "UiMenu.h"

SceneMulti::SceneMulti() : Scene(SceneIds::Multi)
{
}

void SceneMulti::Init()
{
	// 리소스 ID 설정
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
	soundIds.push_back("sound/chop.wav");
	soundIds.push_back("sound/death.wav");
	soundIds.push_back("sound/out_of_time.wav");

	// 오브젝트 추가 (배경 요소)
	AddGameObject(new SpriteGo("graphics/background.png"));

	for (int i = 0; i < 3; ++i)
	{
		BackgroundElement* element = (BackgroundElement*)AddGameObject(new BackgroundElement("graphics/cloud.png"));
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
	tree2 = (Tree*)AddGameObject(new Tree());

	deathSound = (SoundGo*)AddGameObject(new SoundGo("sound/death.wav"));
	timeSound = (SoundGo*)AddGameObject(new SoundGo("sound/out_of_time.wav"));

	player1 = (Player*)AddGameObject(new Player(SCENE_MGR.selectedPlayer1));
	player2 = (Player*)AddGameObject(new Player(SCENE_MGR.selectedPlayer2));

	uiHud2 = (UiHud2*)AddGameObject(new UiHud2());
	uiMenu = (UiMenu*)AddGameObject(new UiMenu());
	score1 = 0;
	score2 = 0;

	if (!backgroundMusic.openFromFile("sound/forest.wav"))
	{
		std::cout << "Fail" << std::endl;
	}
	else
	{
		std::cout << "load" << std::endl;
	}
	Scene::Init();
}

void SceneMulti::Enter()
{
	Scene::Enter();
	isShowMenu = false;
	isPlaying = true;
	isMenu = true;
	timerMax = 5.0f; // 5초

	// 나무 위치 설정
	sf::Vector2f windowW = FRAMEWORK.GetWindowSizeF();
	float treeOffset = 400.0f;
	sf::Vector2f tree1Pos = { windowW.x * 0.5f - treeOffset, 0.0f };
	sf::Vector2f tree2Pos = { windowW.x * 0.5f + treeOffset, 0.0f };

	tree1->SetPosition(tree1Pos);
	tree2->SetPosition(tree2Pos);

	hp1 = 100;
	hp2 = 100;

	// 플레이어 위치 설정
	sf::Vector2f player1Pos = tree1->GetPosition();
	player1Pos.y = 950.0f;
	sf::Vector2f player2Pos = tree2->GetPosition();
	player2Pos.y = 950.0f;

	player1->SetPosition(player1Pos);
	player2->SetPosition(player2Pos);

	// UI
	timer = timerMax;
	uiHud2->SetTimeBar(timer / timerMax);

	deathSound->Reset();
	timeSound->Reset();
	backgroundMusic.stop();
	if (isPlaying && !isShowMenu)
	{
		backgroundMusic.play();
	}

}

void SceneMulti::Update(float dt)
{
	Scene::Update(dt);

	// 배경음악
	if (isPlaying && !isShowMenu)
	{
		if (backgroundMusic.getStatus() != sf::SoundSource::Status::Playing)
			backgroundMusic.play();
	}
	else
	{
		backgroundMusic.stop();
	}

	// 메뉴
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape) && escape)
	{
		isShowMenu = !isShowMenu;
		isPlaying = !isPlaying;
		isMenu = !isMenu;
		uiMenu->SetIsShowMenu(isShowMenu);
	}

	if (isShowMenu)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			uiMenu->ColorSelectedOption("Title");
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Down))
		{
			uiMenu->ColorSelectedOption("Exit");
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Return))
		{
			if (uiMenu->GetIsTitle())
			{
				SCENE_MGR.ChangeScene(SceneIds::Title);
			}
			else if (uiMenu->GetIsExit())
			{
				FRAMEWORK.WindowClose();
			}
		}
	}
	// 일시정지 및 재개
	if (InputMgr::GetKeyDown(sf::Keyboard::Return)&& !isShowMenu && seungYeonCheck)
	{
		timer = timerMax;
		if (seungYeonCheck)
		{
			isPlaying = !isPlaying;
			seungYeonCheck = false;
			escape = true;
			hp1 = 100;
			hp2 = 100;
			score1 = 0;
			score2 = 0;
			uiHud2->Reset();
		}
		if (isPlaying)
		{
			uiHud2->SetShowTitle(false);
			uiHud2->SetShowDetail(false);
			backgroundMusic.stop();
			backgroundMusic.play();
		}
		/*uiHud2->SetTitleMessage("Pause");
		uiHud2->SetDetailMessage("Press Enter Key to Restart");*/
		/*uiHud2->SetShowTitle(true);
		uiHud2->SetShowDetail(true);*/	
	}
	if (isPlaying)
	{
		// 플레이
		FRAMEWORK.SetTimeScale(1);
		timer -= dt;
		// 타이머
		uiHud2->SetTimeBar(timer / timerMax);
		// 제한시간 마감 후
		if (timer <= 0)
		{
			timer = 0;
			isPlaying = false;
			// 점수에 따른 결과 출력
			if (score1 > score2)
			{
				uiHud2->SetTitleMessage("Player 1 Winner!");
				uiHud2->SetDetailMessage("\t\t1st Player 1: " + std::to_string(score1) + "\n\t\t2nd Player 2: " + std::to_string(score2) + "\nPress Enter Key to Restart");
				escape = false;
				seungYeonCheck = true;
			}
			else if (score1 < score2)
			{
				uiHud2->SetTitleMessage("Player 2 Winner!");
				uiHud2->SetDetailMessage("\t\t1st Player 2: " + std::to_string(score2) + "\n\t\t2nd Player 1: " + std::to_string(score1) + "\nPress Enter Key to Restart");
				escape = false;
				seungYeonCheck = true;
			}
			else
			{
				uiHud2->SetTitleMessage("Draw!");
				escape = false;
				seungYeonCheck = true;
			}
			uiHud2->SetShowTitle(true);
			uiHud2->SetShowDetail(true);
		}
		else
		{
			uiHud2->SetShowTitle(false);
			uiHud2->SetShowDetail(false);
		}
		// 플레이어 1 조작
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Left);
			player1->SetDrawAxe(true);
			// 충돌 체크
			if (tree1->GetSide() == player1->GetSide())
			{
				score1 -= 20;
				hp1 -= 20;
				if (score1 <= 0)
				{
					score1 = 0;
				}
			}
			else
			{
				score1 += 10;
			}
			// Score UI 업데이트
			uiHud2->SetScore(score1, 1);
			uiHud2->SetHp(hp1, 1);
			if (hp1 <= 0)
			{
				score1 = 0;
				score2 = 0;
				isPlaying = false;
				uiHud2->SetTitleMessage("Player 2 Winner!");
				uiHud2->SetDetailMessage("Player 1 Died. Press Enter to Restart.");
				uiHud2->SetShowTitle(true);
				uiHud2->SetShowDetail(true);
				escape = false;
				seungYeonCheck = true;
				return;
			}
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			tree1->UpdateBranches();
			player1->SetSide(Sides::Right);
			player1->SetDrawAxe(true);
			// 충돌 체크
			if (tree1->GetSide() == player1->GetSide())
			{
				score1 -= 20;
				hp1 -= 20;
				if (score1 <= 0)
				{
					score1 = 0;
				}
			}
			else
			{
				score1 += 10;
			}
			// Score UI 업데이트
			uiHud2->SetScore(score1, 1);
			uiHud2->SetHp(hp1, 1);
			if (hp1 <= 0)
			{
				isPlaying = false;
				uiHud2->SetTitleMessage("Player 2 Winner!");
				uiHud2->SetDetailMessage("Player 1 Died. Press Enter to Restart.");
				uiHud2->SetShowTitle(true);
				uiHud2->SetShowDetail(true);
				escape = false;
				seungYeonCheck = true;
				return;
			}
		}
		if (InputMgr::GetKeyUp(sf::Keyboard::A) || InputMgr::GetKeyUp(sf::Keyboard::D))
		{
			player1->SetDrawAxe(false);
		}
		// 플레이어 2 조작
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Left);
			player2->SetDrawAxe(true);
			// 충돌 체크
			if (tree2->GetSide() == player2->GetSide())
			{
				score2 -= 20;
				hp2 -= 20;
				if (score2 <= 0)
				{
					score2 = 0;
				}
			}
			else
			{
				score2 += 10;
			}
			// Score UI 업데이트
			uiHud2->SetScore(score2, 2);
			uiHud2->SetHp(hp2, 2);
			if (hp2 <= 0)
			{
				score1 = 0;
				score2 = 0;
				isPlaying = false;
				uiHud2->SetTitleMessage("Player 2 Winner!");
				uiHud2->SetDetailMessage("Player 1 Died. Press Enter to Restart.");
				uiHud2->SetShowTitle(true);
				uiHud2->SetShowDetail(true);
				escape = false;
				seungYeonCheck = true;
				return;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			tree2->UpdateBranches();
			player2->SetSide(Sides::Right);
			player2->SetDrawAxe(true);
			// 충돌 체크
			if (tree2->GetSide() == player2->GetSide())
			{
				score2 -= 20;
				hp2 -= 20;
				if (score2 <= 0)
				{
					score2 = 0;
				}
			}
			else
			{
				score2 += 10;
			}
			// Score UI 업데이트
			uiHud2->SetScore(score2, 2);
			uiHud2->SetHp(hp2, 2);
			if (hp2 <= 0)
			{
				isPlaying = false;
				uiHud2->SetTitleMessage("Player 2 Winner!");
				uiHud2->SetDetailMessage("Player 1 Died. Press Enter to Restart.");
				uiHud2->SetShowTitle(true);
				uiHud2->SetShowDetail(true);
				escape = false;
				seungYeonCheck = true;
				return;
			}

		}
		if (InputMgr::GetKeyUp(sf::Keyboard::Left) || InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			player2->SetDrawAxe(false);
		}
	}
	else
	{
		// 플레이 정지
		FRAMEWORK.SetTimeScale(0);
	}
}
