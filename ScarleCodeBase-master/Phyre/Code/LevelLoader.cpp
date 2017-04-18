#include "LevelLoader.h"
//C++
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

//DXTK

//OURS
#include "../Main_Engine/Platforms.h"
#include "../Main_Engine/Enemy.h"
#include "../Main_Engine/Collectible.h"

Level* LevelLoader::loadLevel(std::string LevelPath)
{
	Level* tmpLevel = new Level();
	Platforms platformsManager(GameData::renderer);

	tmpLevel->playerStartingPosition = new Vec2(0.0f, 100.0f);

	tmpLevel->go_list.push_back(platformsManager.standardPlatform(0.0f, 0.0f, 300.0f, 100.0f, "Platform"));
	return tmpLevel;
}

void LevelLoader::saveLevel(Level * level, std::string LevelPath)
{
	return;
}

Level * LevelLoader::createLevel(std::vector<GameObject*> level, Vec2* playerPos)
{
	Level* tmp = new Level();
	tmp->playerStartingPosition = playerPos;
	for (auto go : level)
	{
		tmp->go_list.push_back(go);
	}

	return tmp;
}