#pragma once
#include "GameObject.h"


class UiHud2 : public GameObject
{
protected:
	sf::RectangleShape timeBar;
	sf::Text textTitle;
	sf::Text textDetail;

	sf::Text textScore1;
	sf::Text textScore2;
	sf::Text textHp1;
	sf::Text textHp2;

	std::string fontId;
	bool isShowTitle;
	bool isShowDetail;

	sf::Vector2f timeBarSize;

public:
	UiHud2(const std::string& name = "");
	~UiHud2() override = default;

	void SetScore(int score, int playerNum);
	void SetHp(int hp, int playerNum);
	void SetTitleMessage(const std::string& msg);
	void SetDetailMessage(const std::string& msg);
	void SetShowTitle(bool show) { isShowTitle = show; }
	void SetShowDetail(bool show) { isShowDetail = show; }
	void SetTimeBar(float value); // 0.f ~ 1.f

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};