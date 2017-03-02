#pragma once
#include <string>
#include <vector>
#include "GameObjectV2.h"
#include "CustomMath.h"

struct Level
{
	Vec2* playerStartingPosition;
	std::vector<GameObjectV2*> go_list;
};

static class LevelLoader
{
public:
	static Level* loadLevel(std::string LevelPath);

protected:
	static std::string getStringFromFile(std::fstream& _file);
	static Vec2* getVectorFromFile(std::fstream& _file);
	static float getFloatFromFile(std::fstream & _file);
	static int getIntFromFile(std::fstream & _file);

};