#include "stdafx.h"
#include "Log.h"

Log::Log(const std::string& name)
	:GameObject(name)
{
}

void Log::DisableLog()
{
	for (int i = 0; i < MAX_LOGS; i++)
	{
		isLogActive[i] = false;
	}
}

void Log::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	for (int i = 0; i < logSize; ++i)
	{
		sprite[i].setPosition(pos);
	}
}

void Log::Init()
{
	texIdLog = "graphics/log.png";
}



void Log::Release()
{
}

void Log::Reset()
{
	sprite.resize(5);
	for (int i = 0; i < logSize; i++)
	{
		sprite[i].setTexture(TEXTURE_MGR.Get(texIdLog));
		logDirection[i] = { 1.f,-1.f };
		logVelocity[i] = logDirection[i] * logSpeed;
		isLogActive[i] = false;
	}

}

void Log::Update(float dt)
{
	if (logActive)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			isLogActive[logIdxCount] = true;
			sprite[logIdxCount].setPosition(800.f, 800.f);
			logDirection[logIdxCount] = { 1.f,-1.f };
			logVelocity[logIdxCount] = logDirection[logIdxCount] * logSpeed;
			logIdxCount++;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			isLogActive[logIdxCount] = true;
			sprite[logIdxCount].setPosition(800.f, 800.f);
			logDirection[logIdxCount] = { -1.f,-1.f };
			logVelocity[logIdxCount] = logDirection[logIdxCount] * logSpeed;
			logIdxCount++;
		}
	}
	
	for (int i = 0; i < logSize; i++)
	{
		if (!isLogActive[i]) 
		{
			continue;
		}
		logVelocity[i] += gravity * dt;

		sf::Vector2f pos = sprite[i].getPosition();
		pos += logVelocity[i] * dt;
		sprite[i].setPosition(pos);
	}
	if (logIdxCount == 4)
	{
		logIdxCount = 0;
	}
	
}

void Log::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < logSize; i++)
	{
		if (isLogActive[i])
		{
			window.draw(sprite[i]);
		}
	}
}
