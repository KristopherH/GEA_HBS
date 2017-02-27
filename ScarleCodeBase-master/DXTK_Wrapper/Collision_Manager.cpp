#include "Collision_Manager.h"
#include "Game_Controller.h"
#include "GameObjectV2.h"
#include "GameDataV2.h"

bool CollisionManager::boxCollision(std::string a_name, std::string b_name)
{
	int a_location = GameDataV2::game_controller->getGameObjectLocation(a_name);
	int b_location = GameDataV2::game_controller->getGameObjectLocation(b_name);

	if (a_location == -1 || b_location == -1)
	{
		OutputDebugString("One or both of the game objects searched for do not exist");
		return false;
	}

	GameObjectV2* a = GameDataV2::go_list.at(a_location);
	GameObjectV2* b = GameDataV2::go_list.at(b_location);

	if (a->getTag() == "Camera" || b->getTag() == "Camera") return false;
	
	if (a->GetPosition().x < b->GetPosition().x + b->GetSize().x &&
		a->GetPosition().x + a->GetSize().x > b->GetPosition().x &&
		a->GetPosition().y < b->GetPosition().y + b->GetSize().y &&
		a->GetPosition().y + a->GetSize().y > b->GetPosition().y)
	{
		a = nullptr;
		b = nullptr;

		//Collision
		return true;
	}

	a = nullptr;
	b = nullptr;

	//No collision
	return false;
}

bool CollisionManager::circleCollision(std::string a, std::string b)
{
	return false;
}
