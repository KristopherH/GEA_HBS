#include "LevelLoader.h"
//C++
#include <fstream>
#include <regex>
#include <sstream>

//DXTK

//OURS
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
		GameObjectV2* go = nullptr;
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
				if (platformType == "SlowPlatform")
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
				else if (platformType == "JumpPlatform")
				{
					go = platformsManager.jumpPlatform(pos->x, pos->y, size->x, size->y, name);
				}
				else if (platformType == "SpeedPlatform")
				{
					go = platformsManager.speedPlatform(pos->x, pos->y, size->x, size->y, name);
				}
				else if (platformType == "StandardPlatform")
				{
					go = platformsManager.standardPlatform(pos->x, pos->y, size->x, size->y, name);
				}
				else if (platformType == "StickyPlatform")
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
			//get positions and give them
			// PLACEHOLDER

			std::vector<Vec2> foo;
			foo.push_back(Vec2(0.0f, 10.0f));
			foo.push_back(Vec2(100.0f, 10.0f));
			foo.push_back(Vec2(200.0f, 300.0f));

			// END PLACEHOLDER
			if (getStringFromFile(fileStream) == "END")
			{
				go = new Enemy(pos, size, rotation, name, foo);
			}
			else
			{
				//ERROR READING FILE
				return nullptr;
			}
		}
		else if (type == "Collectible")
		{
			if (getStringFromFile(fileStream) == "END")
			{
				go = new Collectible(pos, size, rotation, name);
			}
			else
			{
				return nullptr;
			}
		}
		else if (type == "Ladder")
		{
			if (getStringFromFile(fileStream) == "END")
			{
				go = new GameObjectV2(new Sprite("Ladder", GameDataV2::renderer), name, "Climbable");

				go->setPosition(pos);
				go->setSize(size);
				go->setSolid(false);
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			go = new GameObjectV2();
			return nullptr;
		}

		go->setType(type);
		tmpLevel->go_list.push_back(go);
		go = nullptr;
	}
	return tmpLevel;
}

void LevelLoader::saveLevel(Level * level, std::string LevelPath)
{
	std::fstream fileStream;
	fileStream.open(LevelPath);

	if (!fileStream.is_open())
	{
		return;
	}

	saveVectorToFile(fileStream, "PlayerPos: ", level->playerStartingPosition);
	int ObjNumber = level->go_list.size();
	int validObjects = 0;

	for (int i = 0; i < ObjNumber; i++)
	{
		std::string type = level->go_list[i]->getType();
		//Make sure he type of object is accepted
		if (std::find(acceptedTypes.begin(), acceptedTypes.end(), type) != acceptedTypes.end())
		{
			validObjects++;
		}
	}
	saveIntToFile(fileStream, "Objects: ", validObjects);
	int j = 0;
	for (int i = 0; i < ObjNumber; i++)
	{
		std::string type = level->go_list[i]->getType();
		//Make sure he type of object is accepted
		if (std::find(acceptedTypes.begin(), acceptedTypes.end(), type) != acceptedTypes.end())
		{
			fileStream << j << ":\n";
			j++;
			saveStringToFile(fileStream, "Type: ", type);
			saveStringToFile(fileStream, "Name: ", level->go_list[i]->getName());
			saveVectorToFile(fileStream, "Position: ", &level->go_list[i]->getPosition());
			saveVectorToFile(fileStream, "Size: ", &level->go_list[i]->getSize());
			saveIntToFile(fileStream, "Rotation: ", level->go_list[i]->getRotation());

			if (type == "Platform")
			{
				std::string tag = level->go_list[i]->getTag();
				tag.erase(remove_if(tag.begin(), tag.end(), isspace), tag.end());
				saveStringToFile(fileStream, "PlatformType: ", tag);
			}
			saveStringToFile(fileStream, "", "END");
		}
	}
	saveStringToFile(fileStream, "", "END");
	saveStringToFile(fileStream, "", "END");
}

Level * LevelLoader::createLevel(std::vector<GameObjectV2*> level, Vec2* playerPos)
{
	Level* tmp = new Level();
	tmp->playerStartingPosition = playerPos;
	for (auto go : level)
	{
		tmp->go_list.push_back(go);
	}

	return tmp;
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

void LevelLoader::saveStringToFile(std::fstream & _file, std::string label, std::string string)
{
	_file << label << "(" << string << ")\n";
}

void LevelLoader::saveVectorToFile(std::fstream & _file, std::string label, Vec2* data)
{
	_file << label << "(" << data->x << " " << data->y << ")\n";
}

void LevelLoader::saveFloatToFile(std::fstream & _file, std::string label, float data)
{
	_file << label << "(" << data << ")\n";
}

void LevelLoader::saveIntToFile(std::fstream & _file, std::string label, int data)
{
	_file << label << "(" << data << ")\n";
}
