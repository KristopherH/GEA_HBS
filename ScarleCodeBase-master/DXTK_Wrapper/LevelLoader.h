#pragma once
//C++
#include <string>
#include <vector>

//DXTK

//OURS
#include "GameObject.h"
#include "../DXTK_Wrapper/CustomMath.h"

struct Level
{
	Vec2* playerStartingPosition;
	std::vector<GameObject*> go_list;
};

static const std::vector<std::string> acceptedTypes = { "Platform", "Collectible", "Enemy", "Ladder" };

class LevelLoader
{
public:
	static Level* loadLevel(std::string LevelPath);
	static void saveLevel(Level* level, std::string LevelPath);
	static Level* createLevel(std::vector<GameObject*>, Vec2*);

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