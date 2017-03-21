#include "LevelLoader.h"
#include <fstream>
#include <regex>
#include <sstream>
#include "Platforms.h"
#include "Enemy.h"
#include "Collectible.h"

Level* LevelLoader::loadLevel(std::string LevelPath)
{
	Level* tmpLevel = new Level();
	Platforms platformsManager(GameDataV2::renderer);

	std::fstream fileStream;
	fileStream.open(LevelPath);

	if (!fileStream.is_open())
	{
		return nullptr;
	}

	tmpLevel->playerStartingPosition = getVectorFromFile(fileStream);
	int ObjNumber = getIntFromFile(fileStream);


	for (int i = 0; i < ObjNumber; i++)
	{
		GameObjectV2* go;
		std::string index;
		getline(fileStream, index);
		std::string type = getStringFromFile(fileStream);
		std::string name = getStringFromFile(fileStream);
		Vec2* pos = getVectorFromFile(fileStream);
		Vec2* size = getVectorFromFile(fileStream);
		float rotation = getFloatFromFile(fileStream);

		if (type == "Platform")
		{
			std::string platformType = getStringFromFile(fileStream);
			if (getStringFromFile(fileStream) == "END")
			{
				if (platformType == "Slow")
				{
					go = platformsManager.slowPlatform(pos->x, pos->y, size->x, size->y, name);
				}
				else if (platformType == "ConveyorLeft")
				{
					go = platformsManager.conveyorPlatform(pos->x, pos->y, size->x, size->y, name, true);
				}
				else if (platformType == "ConveyorRight")
				{
					go = platformsManager.conveyorPlatform(pos->x, pos->y, size->x, size->y, name, false);
				}
				else if (platformType == "Jump")
				{
					go = platformsManager.jumpPlatform(pos->x, pos->y, size->x, size->y, name);
				}
				else if (platformType == "Speed")
				{
					go = platformsManager.speedPlatform(pos->x, pos->y, size->x, size->y, name);
				}
				else if (platformType == "Standard")
				{
					go = platformsManager.standardPlatform(pos->x, pos->y, size->x, size->y, name);
				}
				else if (platformType == "Sticky")
				{
					go = platformsManager.stickyPlatform(pos->x, pos->y, size->x, size->y, name);
				}
			}
			else
			{
				//ERROR MESSAGE OUTPUT
				return nullptr;
			}
			pos = nullptr;
			size = nullptr;
		}
		else if (type == "Enemy")
		{
			if (getStringFromFile(fileStream) == "END")
			{
				go = new Enemy(pos, size, rotation, name);
			}
			else
			{
				//ERROR READING FILE
			}
		}
		else if (type == "Collectible")
		{
			if (getStringFromFile(fileStream) == "END")
			{
				go = new Collectible(pos, size, rotation, name);
			}
		}
		else if (type == "Ladder")
		{
			
			if (getStringFromFile(fileStream) == "END")
			{
				go = new GameObjectV2(new Sprite("Ladder", GameDataV2::renderer), name, "Climbable");

				go->SetPosition(pos);
				go->SetSize(size);
				go->setSolid(false);
			}
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