#include "Game_Controller.h"
//C++

//DXTK

//OURS
#include "GameDataV2.h"
#include "GameObjectV2.h"

int GameController::getGameObjectLocation(std::string name)
{
	unsigned int i = 0;
	for (auto& current_game_object : *GameDataV2::go_list)
	{
		if (current_game_object->getName() == name)
		{
			return i;
		}

		i++;

		if (i >= GameDataV2::go_list->size())
		{
			return -1;
		}
	}

	return -1;
}
