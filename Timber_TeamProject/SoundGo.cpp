#include "stdafx.h"
#include "SoundGo.h"

SoundGo::SoundGo(const std::string& sId, const std::string& name)
	:GameObject(name),soundId(sId)
{
}

void SoundGo::Init()
{
    if (!soundId.empty())
    {
        if (!music.openFromFile(soundId))
        {
        }
        else
        {
            music.setLoop(true); // 반복 재생 설정
        }
        sound.setBuffer(SOUNDBUFFER_MGR.Get(soundId));
    }
    else
    {
    }
}

void SoundGo::Release()
{
    music.stop();
}

void SoundGo::Reset()
{
    music.stop();
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

void SoundGo::Music()
{
    music.play();
}