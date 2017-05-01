#pragma once
//C++
#include <string>
#include <vector>

//DXTK

//OURS
#include "GameObject.h"
#include "CustomMath.h"

struct Level
{
	std::string name = "NULL";
	std::string path;
	Vec2* playerStartingPosition;
	std::vector<GameObject*> go_list;

	int findCollectibles();
};

static const std::vector<std::string> acceptedTypes = { "Platform", "Collectible", "Enemy", "Ladder" };

class LevelLoader
{
	friend class GameFileLoader;
public:
	static Level* loadLevel(std::string LevelPath);
	static void saveLevel(Level* level, std::string LevelPath);
	static Level* createLevel(std::vector<GameObject*>, Vec2*, Vec2*, std::string name);

protected:
	static std::string getStringFromFile(std::fstream& _file);
	static Vec2* getVectorFromFile(std::fstream& _file);
	static float getFloatFromFile(std::fstream & _file);
	static int getIntFromFile(std::fstream & _file);

	static void saveStringToFile(std::fstream& _file, std::string label, std::string);
	static void saveVectorToFile(std::fstream& _file, std::string label, Vec2*);
	static void saveFloatToFile(std::fstream & _file, std::string label, float);
	static void saveIntToFile(std::fstream & _file, std::string label, int);
};