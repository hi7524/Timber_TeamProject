#include "stdafx.h"
#include "UiMenu.h"


void UiMenu::ColorSelectedOption(std::string option)
{
	if (option == "Title")
	{
		textTitle.setFillColor(sf::Color::Yellow);
		textExit.setFillColor(sf::Color::White);
		SetIsTitle(true);
		SetIsExit(false);
		selectedOption = "Title";
	}
	if (option == "Exit")
	{
		textTitle.setFillColor(sf::Color::White);
		textExit.setFillColor(sf::Color::Yellow);
		SetIsTitle(false);
		SetIsExit(true);
		selectedOption = "Exit";
	}
}

void UiMenu::Init()
{
	// 폰트 ID 설정
	fontId = "fonts/KOMIKAP_.ttf";

}

void UiMenu::Release()
{
}

void UiMenu::Reset()
{
	textMenu.setFont(FONT_MGR.Get(fontId));
	textTitle.setFont(FONT_MGR.Get(fontId));
	textExit.setFont(FONT_MGR.Get(fontId));


	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	textMenu.setPosition(bounds.width * 0.5f, 300);
	textTitle.setPosition(bounds.width * 0.5f, 500);
	textExit.setPosition(bounds.width * 0.5f, 600);


	// 텍스트 설정
	textMenu.setString("MENU");
	textTitle.setString("back to Title");
	textExit.setString("Exit Game");

	textMenu.setCharacterSize(80);
	textTitle.setCharacterSize(50);
	textExit.setCharacterSize(50);

	textMenu.setFillColor(sf::Color::White);
	textTitle.setFillColor(sf::Color::White);
	textExit.setFillColor(sf::Color::White);


	Utils::SetOrigin(textMenu, Origins::MC);
	Utils::SetOrigin(textTitle, Origins::MC);
	Utils::SetOrigin(textExit, Origins::MC);
}

void UiMenu::Update(float dt)
{
}

void UiMenu::Draw(sf::RenderWindow& window)
{
	if (isShowMenu)
	{
		window.draw(textMenu);
		window.draw(textTitle);
		window.draw(textExit);
	}
}