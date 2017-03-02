#include "Collision_Manager.h"
#include "Game_Controller.h"
#include "PlayerV2.h"
#include "BaseCamera.h"
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

	if (!a->isAlive() || !b->isAlive() || !a->GetSprite() || !b->GetSprite())
	{
		return false;
	}

	PlayerV2* player = nullptr;
	BaseCamera* camera = nullptr;
	GameObjectV2* other = nullptr;

	if (a->getTag() == "Player")
	{
		player = static_cast<PlayerV2*>(a);
		/*if (b->getTag() == "Camera")
		{
			camera = static_cast<BaseCamera*>(b);
			camera->setMovementDirection(findCollisionDirection(player, camera));
			return false;
		}*/

		other = b;
	}

	if (b->getTag() == "Player")
	{
		player = static_cast<PlayerV2*>(b);
		/*if (a->getTag() == "Camera")
		{
			camera = static_cast<BaseCamera*>(b);
			camera->setMovementDirection(findCollisionDirection(player, camera));
			return false;
		}*/

		other = a;
	}

	if (a->GetPosition().x < b->GetPosition().x + b->GetSize().x &&
		a->GetPosition().x + a->GetSize().x > b->GetPosition().x &&
		a->GetPosition().y < b->GetPosition().y + b->GetSize().y &&
		a->GetPosition().y + a->GetSize().y > b->GetPosition().y)
	{
		col_direction = findCollisionDirection(a, b);

		if (player && other->getSolid())
		{
			if (col_direction == Direction::LEFT)
			{
				if (player->getMovementDirection() == Direction::RIGHT)
				{
					player->movePosition(new Vec2(-player->getSpeed(), 0.0f));
				}
			}

			if (col_direction == Direction::RIGHT)
			{
				if (player->getMovementDirection() == Direction::LEFT)
				{
					player->movePosition(new Vec2(player->getSpeed(), 0.0f));
				}
			}
		}

		return true;
	}


	//No collision
	return false;
}

bool CollisionManager::circleCollision(std::string a, std::string b)
{
	return false;
}

Direction CollisionManager::getCollisionDirection()
{
	return col_direction;
}

bool CollisionManager::oneWayPlatform(std::string a_name)
{
	if (a_name == "Camera")
		return false;

	int a_location = GameDataV2::game_controller->getGameObjectLocation(a_name);
	int player_location = GameDataV2::game_controller->getGameObjectLocation("Player");

	if (a_location == -1 || player_location == -1)
	{
		OutputDebugString("One or both of the game objects searched for do not exist");
		return false;
	}

	GameObjectV2* a = GameDataV2::go_list.at(a_location);
	GameObjectV2* player = GameDataV2::go_list.at(player_location);

	if (player->GetPosition().y > a->GetPosition().y + a->GetSize().y ||
		player->GetPosition().y + player->GetSize().y < a->GetPosition().y)
	{
		return true;
	}

	return false;
}

Direction CollisionManager::findCollisionDirection(GameObjectV2* a, GameObjectV2* b)
{
	BaseCamera* camera = nullptr;

	float object_a_bot = 0.0f;
	float object_a_right = 0.0f;
	float object_b_bot = 0.0f;
	float object_b_right = 0.0f;

	float top_collision = 0.0f;
	float left_collision = 0.0f;
	float bottom_collision = 0.0f;
	float right_collision = 0.0f;

	if (a->getTag() == "Player" && b->getTag() == "Camera")
	{
		camera = static_cast<BaseCamera*>(b);

		object_a_bot = a->GetPosition().y + a->GetSize().y;
		object_a_right = a->GetPosition().x + a->GetSize().x;
		object_b_bot = camera->getPlayerBoxPosY() + camera->getPlayerBoxHeight();
		object_b_right = camera->getPlayerBoxPosX() + camera->getPlayerBoxWidth();

		top_collision = object_a_bot - camera->getPlayerBoxPosY();
		left_collision = object_a_right - camera->getPlayerBoxPosX();
		bottom_collision = object_b_bot - a->GetPosition().y;
		right_collision = object_b_right - a->GetPosition().x;
	}
	else
	{
		object_a_bot = a->GetPosition().y + a->GetSize().y;
		object_a_right = a->GetPosition().x + a->GetSize().x;
		object_b_bot = b->GetPosition().y + b->GetSize().y;
		object_b_right = b->GetPosition().x + b->GetSize().x;

		top_collision = object_a_bot - b->GetPosition().y;
		left_collision = object_a_right - b->GetPosition().x;
		bottom_collision = object_b_bot - a->GetPosition().y;
		right_collision = object_b_right - a->GetPosition().x;
	}

	if (top_collision < bottom_collision && top_collision < left_collision && top_collision < right_collision)
	{
		return Direction::TOP;
	}
	if (left_collision < top_collision && left_collision < bottom_collision && left_collision < right_collision)
	{
		return Direction::LEFT;
	}
	if (bottom_collision < top_collision && bottom_collision < left_collision && bottom_collision < right_collision)
	{
		return Direction::BOTTOM;
	}
	if (right_collision < top_collision && right_collision < left_collision && right_collision < bottom_collision)
	{
		return Direction::RIGHT;
	}

	return Direction::NONE;
}
