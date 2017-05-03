#pragma once
#include "LevelLoader.h"
#include "SoundManager.h"
#include "Input_Manager.h"

class SettingsLoader
{
public:	
	static void saveSettings(std::string LevelPath = "./GameFiles/Settings.settings");
	static void loadSettings(std::string LevelPath = "./GameFiles/Settings.settings");

};