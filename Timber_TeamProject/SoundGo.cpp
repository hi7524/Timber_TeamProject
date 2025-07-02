#include "stdafx.h"
#include "SoundGo.h"

SoundGo::SoundGo(const std::string& sId, const std::string& name)
	:GameObject(name),soundId(sId)
{
}

void SoundGo::Init()
{
}

void SoundGo::Release()
{
}

void SoundGo::Reset()
{
	sound.setBuffer(SOUNDBUFFER_MGR.Get(soundId));
}

void SoundGo::Update(float dt)
{
}

void SoundGo::Draw(sf::RenderWindow& window)
{
}

void SoundGo::Play()
{
	sound.play();
}
