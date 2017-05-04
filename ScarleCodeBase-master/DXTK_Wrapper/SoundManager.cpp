#include "SoundManager.h"
#include "SoundManager.h"
#ifndef ARCADE

#include "SoundManager.h"
#include "Helper.h"

SoundManager::SoundManager()
{
	// This is only needed in Windows desktop apps
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif

	audioEngine = new DirectX::AudioEngine(eflags);

}

SoundManager::~SoundManager()
{
	delete audioEngine;
	audioEngine = nullptr;
}

void SoundManager::playSound(std::string name, bool BG, bool loop)
{
	std::string filename = "..\\Assets\\Sounds\\";
	filename.append(name);
	if (sounds.find(filename) == sounds.end())
	{
		sounds[filename] = std::make_unique<DirectX::SoundEffect>(audioEngine, Helper::charToWChar(filename.c_str()));
	}
	if (!BG)
	{
		playingSounds.push_back(sounds[filename]->CreateInstance());
		playingSounds[playingSounds.size()-1]->SetVolume(SFX_Volume/100.0f);
		playingSounds[playingSounds.size() - 1]->Play(loop);
	}
	else
	{
		std::unique_ptr<DirectX::SoundEffect> soundEffect;
		soundEffect = std::make_unique<DirectX::SoundEffect>(audioEngine, Helper::charToWChar(filename.c_str()));
		auto effect = soundEffect->CreateInstance();
		effect->Play(loop);
	}
}

void SoundManager::Update()
{
	if (!audioEngine->Update())
	{
		playingSounds.clear();
		// No audio device is active
		if (audioEngine->IsCriticalError())
		{

		}
	}
}

void SoundManager::setMasterVolume(unsigned short _volume)
{
	if (_volume > 100)
	{
		_volume = 100;
	}
	float volume = _volume * 0.01f;
	volume = roundf(volume * 100) / 100;
	audioEngine->SetMasterVolume(volume);
}

void SoundManager::setSFXVolume(unsigned short _volume)
{
	if (_volume > 100)
	{
		_volume = 100;
	}
	SFX_Volume = _volume;
	for (auto& sound : playingSounds)
	{
		sound->SetVolume(SFX_Volume / 100.0f);
	}
}

unsigned short SoundManager::getMasterVolume()
{
	return (round(audioEngine->GetMasterVolume() * 100.0f));
}

unsigned short SoundManager::getSFXVolume()
{
	return SFX_Volume;
}

#else

#include "SoundManager.h"
#include "Helper.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::playSound(std::string name, bool BG, bool loop)
{
	std::string filename = "..\\Assets\\Sounds\\";
	filename.append(name);
	if (loop)
	{
		PlaySound(TEXT(filename.c_str()), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP); 
	}
	else
	{
		PlaySound(TEXT(filename.c_str()), NULL, SND_ASYNC | SND_FILENAME);
	}
}

void SoundManager::Update()
{
}

void SoundManager::setMasterVolume(unsigned short _volume)
{
	if (_volume > 100)
	{
		_volume = 100;
	}
	Volume = _volume;
}

void SoundManager::setSFXVolume(unsigned short _volume)
{
	if (_volume > 100)
	{
		_volume = 100;
	}
	SFX_Volume = _volume;
}

unsigned short SoundManager::getMasterVolume()
{
	return Volume;
}

unsigned short SoundManager::getSFXVolume()
{
	return SFX_Volume;
}
#endif