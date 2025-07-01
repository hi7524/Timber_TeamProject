#pragma once
#include "GameObject.h"


class UiHud2 : public GameObject
{
protected:
	sf::RectangleShape timeBar;
	sf::Text textMessage;

	sf::Text textScore1;
	sf::Text textScore2;

	std::string fontId;
	bool isShowMessage;

	sf::Vector2f timeBarSize;

public:
	UiHud2(const std::string& name = "");
	~UiHud2() override = default;

	void SetScore(int score, int playerNum);
	void SetMessage(const std::string& msg);
	void SetShowMassage(bool show) { isShowMessage = show; }
	void SetTimeBar(float value); // 0.f ~ 1.f

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};