#include "stdafx.h"
#include "UiHud2.h"


UiHud2::UiHud2(const std::string& name) : GameObject(name)
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

		Utils::SetOrigin(textScore2, Origins::TR);
		textScore2.setPosition(1920 - 20, 20);
	}
}

void UiHud2::SetTitleMessage(const std::string& msg)
{
	textTitle.setString(msg);

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	Utils::SetOrigin(textTitle, Origins::MC);
	textTitle.setPosition(bounds.width * 0.5f, bounds.height * 0.5f - 100);
	textTitle.setFillColor(sf::Color::Yellow);
}

void UiHud2::SetDetailMessage(const std::string& msg)
{
	textDetail.setString(msg);

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	Utils::SetOrigin(textDetail, Origins::TC);
	textDetail.setPosition(bounds.width * 0.5f, bounds.height * 0.5f);
}

void UiHud2::SetTimeBar(float value)
{
	timeBar.setSize({ timeBarSize.x * value, timeBarSize.y });
}

void UiHud2::Init()
{
	fontId = "fonts/KOMIKAP_.ttf";

	
}

void UiHud2::Release()
{
}

void UiHud2::Reset()
{
	textScore1.setFont(FONT_MGR.Get(fontId));
	textScore2.setFont(FONT_MGR.Get(fontId));
	textTitle.setFont(FONT_MGR.Get(fontId));
	textDetail.setFont(FONT_MGR.Get(fontId));

	SetScore(0, 1);
	SetScore(0, 2);

	Utils::SetOrigin(textScore1, Origins::TL);
	Utils::SetOrigin(textScore2, Origins::TR);

	textScore1.setPosition(20, 20);
	textScore2.setPosition(1920 - 20, 20);

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	// 텍스트 UI 설정


	textScore1.setCharacterSize(50);
	textScore2.setCharacterSize(50);

	textScore1.setFillColor(sf::Color::White);
	textScore2.setFillColor(sf::Color::White);

	textScore1.setPosition(20, 20);
	textScore2.setPosition(1920 - 20, 20);

	textTitle.setCharacterSize(80);
	textDetail.setCharacterSize(50);

	// 타임바 UI 설정
	timeBarSize = { 400.f, 40.f };
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setSize(timeBarSize);

	Utils::SetOrigin(timeBar, Origins::BL);

	timeBar.setPosition(bounds.width * 0.5f - timeBarSize.x * 0.5f, 100.f);

	Utils::SetOrigin(textScore1, Origins::TL);
	Utils::SetOrigin(textScore2, Origins::TR);
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
	if (isShowTitle)
	{
		window.draw(textTitle);
	}
	if (isShowDetail)
	{
		window.draw(textDetail);
	}

	// 타임바 UI
	window.draw(timeBar);
}