#include "Collision_Manager.h"
#include "Game_Controller.h"
#include "PlayerV2.h"
#include "BaseCamera.h"
#include "GameDataV2.h"
#include <string>

bool CollisionManager::boxCollision(std::string a_name, std::string b_name)
{
	int a_location = GameDataV2::game_controller->getGameObjectLocation(a_name);
	int b_location = GameDataV2::game_controller->getGameObjectLocation(b_name);

	if (a_location == -1 || b_location == -1)
	{
		OutputDebugString("One or both of the game objects searched for do not exist\n");
		return false;
	}

	GameObjectV2* a = GameDataV2::go_list.at(a_location);
	GameObjectV2* b = GameDataV2::go_list.at(b_location);

	if (!a->getAlive() || !b->getAlive() || !a->getSprite() || !b->getSprite())
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

	if (a->getPosition().x < b->getPosition().x + b->getSize().x &&
		a->getPosition().x + a->getSize().x > b->getPosition().x &&
		a->getPosition().y < b->getPosition().y + b->getSize().y &&
		a->getPosition().y + a->getSize().y > b->getPosition().y)
	{
		col_direction = findCollisionDirection(a, b);

		/*if (player && other->getSolid())
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
		}*/

		return true;
	}


	//No collision
	return false;
}

bool CollisionManager::boxCollision(Rect a, Rect b)
{

	if (a.min.x < b.max.x &&
		a.max.x > b.min.x &&
		a.min.y < b.max.y &&
		a.max.y > b.min.y)
	{
		return true;
		findCollisionDirection(&a, &b);
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

	if (player->getPosition().y > a->getPosition().y + a->getSize().y ||
		player->getPosition().y + player->getSize().y < a->getPosition().y)
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

	if (a->getName() == "Player" && b->getName() == "Camera")
	{
		camera = static_cast<BaseCamera*>(b);

		object_a_bot = a->getPosition().y + a->getSize().y;
		object_a_right = a->getPosition().x + a->getSize().x;
		object_b_bot = camera->getPlayerBoxPosY() + camera->getPlayerBoxHeight();
		object_b_right = camera->getPlayerBoxPosX() + camera->getPlayerBoxWidth();

		top_collision = object_a_bot - camera->getPlayerBoxPosY();
		left_collision = object_a_right - camera->getPlayerBoxPosX();
		bottom_collision = object_b_bot - a->getPosition().y;
		right_collision = object_b_right - a->getPosition().x;
	}
	else
	{
		object_a_bot = a->getPosition().y + a->getSize().y;
		object_a_right = a->getPosition().x + a->getSize().x;
		object_b_bot = b->getPosition().y + b->getSize().y;
		object_b_right = b->getPosition().x + b->getSize().x;

		top_collision = object_a_bot - b->getPosition().y;
		left_collision = object_a_right - b->getPosition().x;
		bottom_collision = object_b_bot - a->getPosition().y;
		right_collision = object_b_right - a->getPosition().x;
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

Direction CollisionManager::findCollisionDirection(Rect* a, Rect* b)
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

	object_a_bot = a->max.y;
	object_a_right = a->max.x;
	object_b_bot = b->max.y;
	object_b_right = b->max.x;

	top_collision = object_a_bot - b->min.y;
	left_collision = object_a_right - b->min.x;
	bottom_collision = object_b_bot - a->min.y;
	right_collision = object_b_right - a->min.x;

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
