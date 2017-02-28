#include "LevelLoader.h"
#include <fstream>
#include <regex>
#include <sstream>
#include "Platforms.h"

Level* LevelLoader::loadLevel(std::string LevelPath)
{
	Level* tmpLevel = new Level();
	Platforms platformsManager;

	std::fstream fileStream;
	fileStream.open(LevelPath);

	if (!fileStream.is_open())
	{
		return nullptr;
	}

	tmpLevel->playerStartingPosition = *getVectorFromFile(fileStream);
	int ObjNumber = getIntFromFile(fileStream);


	for (int i = 0; i < ObjNumber; i++)
	{
		GameObjectV2* go;
		std::string index;
		getline(fileStream, index);
		std::string type = getStringFromFile(fileStream);
		if (type == "Platform")
		{
			std::string name = getStringFromFile(fileStream);
			Vec2* pos = getVectorFromFile(fileStream);
			Vec2* size = getVectorFromFile(fileStream);
			float rotation = getFloatFromFile(fileStream);
			if (getStringFromFile(fileStream) == "END")
			{
				go = platformsManager.slowPlatform(GameDataV2::renderer, pos->x, pos->y, size->x, size->y, name);
			}
			else
			{
				//ERROR MESSAGE READING FILE
				return nullptr;
			}
			pos = nullptr;
			size = nullptr;
		}
		else if (type == "Enemy")
		{

		}
		else if (type == "Collectible")
		{

		}
		else
		{
			//ERROR MESSAGE READING FILE
			return nullptr;
		}

		tmpLevel->go_list.push_back(go);
		go = nullptr;
	}
	return tmpLevel;
}

std::string LevelLoader::getStringFromFile(std::fstream& _file)
{
	std::string tmp;
	getline(_file, tmp);
	std::string start = "(";
	std::string end = ")";
	std::string token = tmp.substr(tmp.find(start) + 1, tmp.find(end) - tmp.find(start) - 1); // token is whatever is inbetween ()
	return token;
}

Vec2* LevelLoader::getVectorFromFile(std::fstream& _file)
{
	std::string tmp;
	getline(_file, tmp);
	std::string start = "(";
	std::string end = ")";
	std::string token = tmp.substr(tmp.find(start) + 1, tmp.find(end) - tmp.find(start) - 1); // token is whatever is inbetween ()
	
	string buf; // Have a buffer string
	stringstream ss(token); // Insert the string into a stream

	float x, y;
	ss >> x;
	ss >> y;

	return new Vec2(x, y);
}

float LevelLoader::getFloatFromFile(std::fstream& _file)
{
	std::string tmp;
	getline(_file, tmp);
	std::string start = "(";
	std::string end = ")";
	std::string token = tmp.substr(tmp.find(start) + 1, tmp.find(end) - tmp.find(start) - 1); // token is whatever is inbetween ()
	return stof(token);
}

int LevelLoader::getIntFromFile(std::fstream& _file)
{
	std::string tmp;
	getline(_file, tmp);
	std::string start = "(";
	std::string end = ")";
	std::string token = tmp.substr(tmp.find(start) +1, tmp.find(end) - tmp.find(start) -1); // token is whatever is inbetween ()
	return stoi(token);
}