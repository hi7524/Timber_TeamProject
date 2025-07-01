#include "stdafx.h"
#include "UiHud2.h"



UiHud2::UiHud2(const std::string& name)
	:GameObject(name)
{
}

void UiHud2::SetScore(int score, int playerNum)
{
	if (playerNum == 1)
	{
		static std::string formatScore = "SCORE: ";
		textScore1.setString(formatScore + std::to_string(score));
	}

	if (playerNum == 2)
	{
		static std::string formatScore = "SCORE: ";
		textScore2.setString(formatScore + std::to_string(score));
	}
}

void UiHud2::Init()
{
	fontId = "fonts/KOMIKAP_.ttf";

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	// 텍스트 UI 설정
	Utils::SetOrigin(textScore1, Origins::TL);
	Utils::SetOrigin(textScore2, Origins::TL);

	textScore1.setCharacterSize(50);
	textScore2.setCharacterSize(50);

	textScore1.setFillColor(sf::Color::White);
	textScore2.setFillColor(sf::Color::White);

	textScore1.setPosition(20, 20);
	textScore2.setPosition(bounds.width * 0.5f + 20, 20);




	// 타임바 UI 설정
	timeBarSize = { 400.f, 80.f };
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setSize(timeBarSize);

	Utils::SetOrigin(timeBar, Origins::BL);

	timeBar.setPosition(bounds.width * 0.5f - timeBarSize.x * 0.5f, bounds.height - 100.f);
}

void UiHud2::Release()
{
}

void UiHud2::Reset()
{
	textScore1.setFont(FONT_MGR.Get(fontId));
	textScore2.setFont(FONT_MGR.Get(fontId));
	textMessage.setFont(FONT_MGR.Get(fontId));

	SetScore(0, 1);
	SetScore(0, 2);

	//SetScore(0);
	//isShowMessage = true;
	//SetMessage("Message!");
	//SetTimeBar(1.0f);
}

void UiHud2::Update(float dt)
{
}

void UiHud2::Draw(sf::RenderWindow& window)
{
	// 점수 텍스트 UI
	window.draw(textScore1);
	window.draw(textScore2);

	// 정보 텍스트 UI
	if (isShowMessage)
	{
		window.draw(textMessage);
	}

	// 타임바 UI
	window.draw(timeBar);
}