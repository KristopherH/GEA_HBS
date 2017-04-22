#pragma once

#ifndef ARCADE

#include <string>
#include <d3d11.h>
#include <Audio.h>
#include <map>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void playSound(std::string name, bool BG = false, bool loop = false);

	void Update();

	void setMasterVoume(unsigned short _volume);
	void setSFXVoume(unsigned short _volume);

private:
	
	DirectX::AudioEngine* audioEngine;
	std::map<std::string, std::unique_ptr<DirectX::SoundEffect>> sounds;
	std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> playingSounds;
	unsigned short Volume = 50;
	unsigned short SFX_Volume = 50;
};

#endif