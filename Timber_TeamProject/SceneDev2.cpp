#include "stdafx.h"
#include "SceneDev2.h"

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

	player1 = (Player*)AddGameObject(new Player(SCENE_MGR.selectedPlayer));
	player2 = (Player*)AddGameObject(new Player(SCENE_MGR.selectedPlayer));

	uiHud2 = (UiHud2*)AddGameObject(new UiHud2());

	Scene::Init();
}

void SceneDev2::Enter()
{
}

void SceneDev2::Init()
{
}

void SceneDev2::Update(float dt)
{
}
