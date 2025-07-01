#pragma once
#include "GameObject.h"
#include "Tree.h" 
class Log : public GameObject
{
protected:
	static const int MAX_LOGS = 5;

	std::string texIdLog;
	std::vector<sf::Sprite> sprite;
	sf::Vector2f gravity = { 0.f, 6000.f };
	sf::Vector2f logDirection[MAX_LOGS];  
	sf::Vector2f logVelocity[MAX_LOGS]; 
	Tree tree;
	int logSize = sizeof(logDirection) / sizeof(logDirection[0]);
	int logIdxCount = 0;
	float logSpeed = 2000.f;
	bool isLogActive[MAX_LOGS];

public:
	Log(const std::string& name = "");
	~Log() override = default;

	void DisableLog();
	void SetPosition(const sf::Vector2f& pos) override;

	void Init() override;

	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

};

