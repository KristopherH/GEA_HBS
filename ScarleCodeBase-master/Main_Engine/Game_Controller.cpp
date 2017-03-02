#include "Game_Controller.h"
#include "GameDataV2.h"
#include "GameObjectV2.h"

int GameController::getGameObjectLocation(std::string name)
{
	int i = 0; 

	for (auto& current_game_object : GameDataV2::go_list)
	{
		if (current_game_object->getName() == name)
		{
			return i;
		}

		i++;

		if (i >= GameDataV2::go_list.size())
		{
			return -1;
		}
	}

	return -1;
}
