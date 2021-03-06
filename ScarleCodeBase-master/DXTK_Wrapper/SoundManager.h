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
	void stopSound();

	void Update();

	void setMasterVolume(unsigned short _volume);
	void setSFXVolume(unsigned short _volume);

	unsigned short getMasterVolume();
	unsigned short getSFXVolume();

private:
	
	DirectX::AudioEngine* audioEngine;
	std::map<std::string, std::unique_ptr<DirectX::SoundEffect>> sounds;
	std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> playingSounds;
	unsigned short Master_Volume = 50;
	unsigned short SFX_Volume = 50;
};

#else

#include <string>
#include <windows.h>
#include <map>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void stopSound();

	void playSound(std::string name, bool BG = false, bool loop = false);

	void Update();

	void setMasterVoume(unsigned short _volume);
	void setSFXVoume(unsigned short _volume);

private:

	unsigned short Volume = 50;
	unsigned short SFX_Volume = 50;
};

#endif