#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SpriteGo.h"


class SceneSelectModMulti : public Scene
{
protected:
	int selectedNum1 = 0;
	int selectedNum2 = 0;

	std::string textureId[3] = { "graphics/player.png", "graphics/player1.png", "graphics/player2.png" };

	SpriteGo* character1 = new SpriteGo("graphics/player.png");
	SpriteGo* character2 = new SpriteGo("graphics/player.png");

	TextGo* textKeyR1 = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* textKeyL1 = new TextGo("fonts/KOMIKAP_.ttf");

	TextGo* textKeyR2 = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* textKeyL2 = new TextGo("fonts/KOMIKAP_.ttf");

	TextGo* textReady1 = new TextGo("fonts/KOMIKAP_.ttf");
	TextGo* textReady2 = new TextGo("fonts/KOMIKAP_.ttf");

	TextGo* title;
	TextGo* detail;
	TextGo* player1Name;
	TextGo* player2Name;

	bool isReady1 = false;
	bool isReady2 = false;

public:
	SceneSelectModMulti();
	~SceneSelectModMulti() override = default;

	void Enter() override;
	void Init() override;
	void Update(float dt) override;
};