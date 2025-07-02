#pragma once
#include "GameObject.h"
#include "TextGo.h"

class UiMenu : public GameObject
{
protected:
	sf::Text textMenu;
	sf::Text textTitle;
	sf::Text textExit;

	bool title;
	bool exit;

	std::string fontId;

	bool isShowMenu = false;
	std::string selectedOption = "";

public:
	void SetIsShowMenu(bool show) { isShowMenu = show; }
	void ColorSelectedOption(std::string option);
	std::string GetSelectedOption() { return selectedOption; }

	bool GetIsTitle() { return title; };
	bool GetIsExit() { return exit; };

	void SetIsTitle(bool bo) { title = bo; };
	void SetIsExit(bool bo) { exit = bo; };
	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};