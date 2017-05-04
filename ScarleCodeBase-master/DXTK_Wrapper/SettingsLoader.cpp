#include "SettingsLoader.h"
#include <fstream>
#include "GameData.h"

void SettingsLoader::saveSettings(std::string filePath)
{
	std::fstream fileStream;
	fileStream.open(filePath, fstream::out);

	if (!fileStream.is_open())
	{
		return;
	}
	LevelLoader::saveIntToFile(fileStream, "Volume: ", GameData::sound_manager->getMasterVolume());

	LevelLoader::saveIntToFile(fileStream, "SFX: ", GameData::sound_manager->getSFXVolume());

	LevelLoader::saveIntToFile(fileStream, "KeyNumber: ", GameData::inputManager->key_inputs.size());
	for (auto& key : GameData::inputManager->key_inputs)
	{
		LevelLoader::saveIntToFile(fileStream, GameData::inputManager->key_effect_names[key.first], key.second);
	}
}

void SettingsLoader::loadSettings(std::string filePath)
{
	std::fstream fileStream;
	fileStream.open(filePath);

	if (!fileStream.is_open())
	{
		return;
	}
	int volume = LevelLoader::getIntFromFile(fileStream);
	GameData::sound_manager->setMasterVolume(volume);

	int sfx = LevelLoader::getIntFromFile(fileStream);
	GameData::sound_manager->setSFXVolume(sfx);

	int numberOfKeys = LevelLoader::getIntFromFile(fileStream);
	if (GameData::inputManager->key_inputs.size() == numberOfKeys)
	{
		for (auto& key : GameData::inputManager->key_inputs)
		{
			int newKey = LevelLoader::getIntFromFile(fileStream);
			key.second = newKey;
		}
	}
}
