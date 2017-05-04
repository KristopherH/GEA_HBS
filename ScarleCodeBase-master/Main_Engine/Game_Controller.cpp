#include "Game_Controller.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "GameObject.h"

int GameController::getGameObjectLocation(std::string name)
{
	unsigned int i = 0;
	for (auto& current_game_object : *GameData::go_list)
	{
		if (current_game_object->getName() == name)
		{
			return i;
		}

		i++;

		if (i >= GameData::go_list->size())
		{
			return -1;
		}
	}

	return -1;
}