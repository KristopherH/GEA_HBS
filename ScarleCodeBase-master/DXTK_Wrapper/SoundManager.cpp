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
	if (!BG)
	{
		std::unique_ptr<DirectX::SoundEffect> soundEffect;
		soundEffect = std::make_unique<DirectX::SoundEffect>(audioEngine, Helper::charToWChar(filename.c_str()));
		auto effect = soundEffect->CreateInstance();
		effect->SetVolume(SFX_Volume);
		effect->Play(loop);
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
		// No audio device is active
		if (audioEngine->IsCriticalError())
		{
		}
	}
}

void SoundManager::setMasterVoume(unsigned short _volume)
{
	audioEngine->SetMasterVolume(_volume / 100);
}

void SoundManager::setSFXVoume(unsigned short _volume)
{
	SFX_Volume = _volume;
}