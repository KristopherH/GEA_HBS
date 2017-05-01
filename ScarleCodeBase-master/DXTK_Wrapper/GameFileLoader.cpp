#include "GameFileLoader.h"
#include <fstream>

GameFile * GameFileLoader::loadGame(std::string LevelPath)
{
	std::fstream fileStream;
	fileStream.open(LevelPath);

	if (!fileStream.is_open())
	{
		return nullptr;
	}

	GameFile* game = new GameFile();
	game->lives = LevelLoader::getIntFromFile(fileStream);
	game->collectibles = LevelLoader::getIntFromFile(fileStream);
	int numberOfLevels = LevelLoader::getIntFromFile(fileStream);
	for (int i = 0; i < numberOfLevels; i++)
	{
		std::string index;
		getline(fileStream, index);
		std::string name = LevelLoader::getStringFromFile(fileStream);
		std::string path = LevelLoader::getStringFromFile(fileStream);
		Level* lvl = LevelLoader::loadLevel(path);
		lvl->name = name;
		lvl->path = path;
		game->addLevel(*lvl);
		delete lvl;
	}
	return game;
}

void GameFileLoader::saveGameFile(GameFile * game, std::string LevelPath)
{
	std::fstream fileStream;
	fileStream.open(LevelPath, fstream::out);

	if (!fileStream.is_open())
	{
		return;
	}

	LevelLoader::saveIntToFile(fileStream, "Lives:", game->lives);
	LevelLoader::saveIntToFile(fileStream, "Collectibles:", game->collectibles);
	LevelLoader::saveIntToFile(fileStream, "Levels:", game->levels.size());
	for (int i = 1; i <= game->levels.size(); i++)
	{
		fileStream << i << ":\n";
		LevelLoader::saveStringToFile(fileStream, "Name:", game->levels[i - 1].name);
		LevelLoader::saveStringToFile(fileStream, "Path:", game->levels[i - 1].path);
		//LevelLoader::saveLevel(&game->levels[i - 1], game->levels[i - 1].path);
	}
}

GameFile * GameFileLoader::createGameFIle(Level firstLevel, int lives)
{
	GameFile* game = new GameFile();
	game->lives = lives;
	game->addLevel(firstLevel);
	return game;
}

void GameFile::addLevel(Level lvl)
{
	levels.push_back(lvl);
	collectibles += lvl.findCollectibles();
}
