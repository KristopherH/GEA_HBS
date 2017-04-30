#pragma once
#include "LevelLoader.h"

struct GameFile
{
	int lives = 3;
	int collectibles = 0;
	std::vector<Level> levels;

	void addLevel(Level lvl);
};

class GameFileLoader
{
public:
	static GameFile* loadGame(std::string LevelPath = "./GameFiles/GameFile.game");
	static void saveGameFile(GameFile* game, std::string LevelPath = "./GameFiles/GameFile.game");
	static GameFile* createGameFIle(Level firstLevel, int lives);
};