#pragma once
#include "GameObject.h"
#include <SFML/Audio.hpp>
class SoundGo : public GameObject
{
protected:
	sf::Sound sound;
	sf::Music music;
	std::string soundId;
public:
	SoundGo(const std::string& sId = "", const std::string& name = "");
	~SoundGo() override = default;

	const std::string& GetTextureId() const { return soundId; }
	void SetSoundId(const std::string& sId) { soundId = sId; }

	sf::Sound& GetSound() { return sound; }
	const sf::Sound& GetSound() const { return sound; }

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Play(); //sf::sound
	void Music(); //sf::music
};


