#include "stdafx.h"
#include "SceneSelectModMulti.h"
#include "SpriteGo.h"
#include "TextGo.h"


SceneSelectModMulti::SceneSelectModMulti()
	: Scene(SceneIds::CharChoiceMulti)
{

}

void SceneSelectModMulti::Enter()
{
	Scene::Enter();

	selectedNum1 = 0;
	selectedNum2 = 0;
	isReady1 = false;
	isReady2 = false;

	// �ʱ� �ؽ�ó ����
	character1->SetTextureId(textureId[0]);
	character2->SetTextureId(textureId[0]);

	character1->Reset();
	character2->Reset();

	// �ؽ�Ʈ ���� �ʱ�ȭ
	textReady1->SetFillColor(sf::Color::Transparent);
	textReady2->SetFillColor(sf::Color::Transparent);

	textKeyL1->SetFillColor(sf::Color(64, 64, 64));
	textKeyR1->SetFillColor(sf::Color::White);
	textKeyL2->SetFillColor(sf::Color(64, 64, 64));
	textKeyR2->SetFillColor(sf::Color::White);
}

void SceneSelectModMulti::Init()
{
	// ���ҽ� ����
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/player1.png");
	texIds.push_back("graphics/player2.png");

	fontIds.push_back("fonts/KOMIKAP_.ttf");

	TextGo* title = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* detail = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* player1Name = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* player2Name = new TextGo("fonts/KOMIKAP_.ttf");
	
	// �ؽ�Ʈ ����
	title->SetString("Choose your character!");
	title->SetFillColor(sf::Color::White);
	title->SetCharacterSize(70);

	detail->SetString("- press 'Q', 'P' to ready -");
	detail->SetFillColor(sf::Color::White);
	detail->SetCharacterSize(35);

	player1Name->SetString("player 1");
	player1Name->SetFillColor(sf::Color::White);
	player1Name->SetCharacterSize(30);

	player2Name->SetString("player 2");
	player2Name->SetFillColor(sf::Color::White);
	player2Name->SetCharacterSize(30);

	textKeyL1->SetString("A");
	textKeyL1->SetFillColor(sf::Color(64, 64, 64));
	textKeyL1->SetCharacterSize(25);

	textKeyR1->SetString("D");
	textKeyR1->SetFillColor(sf::Color::White);
	textKeyR1->SetCharacterSize(25);

	textKeyL2->SetString("<-");
	textKeyL2->SetFillColor(sf::Color(64, 64, 64));
	textKeyL2->SetCharacterSize(25);

	textKeyR2->SetString("->");
	textKeyR2->SetFillColor(sf::Color::White);
	textKeyR2->SetCharacterSize(25);

	textReady1->SetString("READY");
	textReady1->SetFillColor(sf::Color::Transparent);
	textReady1->SetCharacterSize(50);

	textReady2->SetString("READY");
	textReady2->SetFillColor(sf::Color::Transparent);
	textReady2->SetCharacterSize(50);

	// Origin ����
	title->SetOrigin(Origins::MC);
	detail->SetOrigin(Origins::MC);
	character1->SetOrigin(Origins::MC);
	character2->SetOrigin(Origins::MC);
	player1Name->SetOrigin(Origins::MC);
	player2Name->SetOrigin(Origins::MC);
	textReady1->SetOrigin(Origins::MC);
	textReady2->SetOrigin(Origins::MC);

	// GameObject �߰�
	AddGameObject(title);
	AddGameObject(detail);
	AddGameObject(character1);
	AddGameObject(character2);
	AddGameObject(player1Name);
	AddGameObject(player2Name);
	AddGameObject(textReady1);
	AddGameObject(textReady2);

	AddGameObject(textKeyL1);
	AddGameObject(textKeyR1);
	AddGameObject(textKeyL2);
	AddGameObject(textKeyR2);

	// ������Ʈ���� ��ġ ����
	sf::Vector2f windowW = FRAMEWORK.GetWindowSizeF();

	character1->SetPosition({ windowW.x * 0.5f - 325.0f, 600 });
	character2->SetPosition({ windowW.x * 0.5f + 325.0f, 600 });

	title->SetPosition({ windowW.x * 0.5f, 130.0f });
	detail->SetPosition({ windowW.x * 0.5f, title->GetPosition().y + 100.0f });

	float textOffset = -155.0f;

	sf::Vector2f playerPos1 = character1->GetPosition();
	sf::Vector2f playerPos2 = character2->GetPosition();
	player1Name->SetPosition({ playerPos1.x, playerPos1.y + textOffset });
	player2Name->SetPosition({ playerPos2.x, playerPos2.y + textOffset });
	textReady1->SetPosition({ playerPos1.x, playerPos1.y + 200 });
	textReady2->SetPosition({ playerPos2.x, playerPos2.y + 200 });

	textKeyL1->SetPosition({ playerPos1.x - 140.0f, playerPos1.y });
	textKeyR1->SetPosition({ playerPos1.x + 140.0f, playerPos1.y});
	textKeyL2->SetPosition({ playerPos2.x - 140.0f, playerPos2.y });
	textKeyR2->SetPosition({ playerPos2.x + 140.0f, playerPos2.y });
	
	Scene::Init();
}

void SceneSelectModMulti::Update(float dt)
{
	Scene::Update(dt);
	
	// Ready ���� ����
	if (InputMgr::GetKeyDown(sf::Keyboard::Q))
	{
		isReady1 = !isReady1;

		// ���� ���ο� ���� ���� ����
		if (isReady1)
		{
			textReady1->SetFillColor(sf::Color::Green);
		}
		else
		{
			textReady1->SetFillColor(sf::Color::Transparent);
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::P))
	{
		isReady2 = !isReady2;

		// ���� ���ο� ���� ���� ����
		if (isReady2)
		{
			textReady2->SetFillColor(sf::Color::Green);
		}
		else
		{
			textReady2->SetFillColor(sf::Color::Transparent);
		}
	}

	if (!isReady1)
	{
		// �÷��̾� 1 ����
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			if (selectedNum1 > 0)
			{
				selectedNum1--;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			if (selectedNum1 < 2)
			{
				selectedNum1++;
			}
		}

		// �̵� ���� ���ο� ���� ���� ����Ű ���� ����
		if (selectedNum1 == 2)
		{
			textKeyR1->SetFillColor(sf::Color(64, 64, 64));
		}
		else
		{
			textKeyR1->SetFillColor(sf::Color::White);
		}

		if (selectedNum1 == 0)
		{
			textKeyL1->SetFillColor(sf::Color(64, 64, 64));
		}
		else
		{
			textKeyL1->SetFillColor(sf::Color::White);
		}
		character1->SetTextureId(textureId[selectedNum1]);
		character1->Reset();
	}
	else
	{
		textKeyR1->SetFillColor(sf::Color::Transparent);
		textKeyL1->SetFillColor(sf::Color::Transparent);
	}
	
	if (!isReady2)
	{
		// �÷��̾� 2 ����
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			if (selectedNum2 > 0)
			{
				selectedNum2--;
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			if (selectedNum2 < 2)
			{
				selectedNum2++;
			}
		}

		// �̵� ���� ���ο� ���� ���� ����Ű ���� ����
		if (selectedNum2 ==  2)
		{
			textKeyR2->SetFillColor(sf::Color(64, 64, 64));
		}
		else
		{
			textKeyR2->SetFillColor(sf::Color::White);
		}

		if (selectedNum2 == 0)
		{
			textKeyL2->SetFillColor(sf::Color(64, 64, 64));
		}
		else
		{
			textKeyL2->SetFillColor(sf::Color::White);
		}

		character2->SetTextureId(textureId[selectedNum2]);
		character2->Reset();
	}
	else
	{
		textKeyR2->SetFillColor(sf::Color::Transparent);
		textKeyL2->SetFillColor(sf::Color::Transparent);
	}

	if (isReady1 && isReady2)
	{
		SCENE_MGR.selectedPlayer1 = textureId[selectedNum1];
		SCENE_MGR.selectedPlayer2 = textureId[selectedNum2];

		SCENE_MGR.ChangeScene(SceneIds::Multi);
	}
}