#include "Collision_Manager.h"
#include "Game_Controller.h"
#include "PlayerV2.h"
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
	PlayerV2* player = nullptr;

	bool player_present = false;

	if (a->getTag() == "Player")
	{
		player = static_cast<PlayerV2*>(a);
		player_present = true;
	}

	if (b->getTag() == "Player")
	{
		player = static_cast<PlayerV2*>(b);
		player_present = true;
	}

	if (a->GetPosition().x < b->GetPosition().x + b->GetSize().x &&
		a->GetPosition().x + a->GetSize().x > b->GetPosition().x &&
		a->GetPosition().y < b->GetPosition().y + b->GetSize().y &&
		a->GetPosition().y + a->GetSize().y > b->GetPosition().y)
	{
		/*KeyBindsHold['a'] = std::bind(&PlayerV2::OnMove, this, Vec2(-speed, 0.0f));
		KeyBindsHold['d'] = std::bind(&PlayerV2::OnMove, this, Vec2(speed, 0.0f));
		KeyBindsHold['w'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, -speed));
		KeyBindsHold['s'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, speed));*/
		col_direction = findCollisionDirection(*a, *b);

		if (player)
		{
			if (col_direction == Direction::TOP)
			{
				if (player->getMovementDirection() == Direction::BOTTOM)
				{
					//player->movePosition(new Vec2(0.0f, player->getSpeed()));
				}
			}

			if (col_direction == Direction::LEFT)
			{
				if (player->getMovementDirection() == Direction::RIGHT)
				{
					if (player)
					{
						player->movePosition(new Vec2(-player->getSpeed(), 0.0f));
					}
				}
			}

			if (col_direction == Direction::BOTTOM)
			{
				if (player->getMovementDirection() == Direction::TOP)
				{
					if (player)
					{
						player->movePosition(new Vec2(0.0f, -player->getSpeed()));
					}
				}
			}

			if (col_direction == Direction::RIGHT)
			{
				if (player->getMovementDirection() == Direction::BOTTOM)
				{
					if (player)
					{
						player->movePosition(new Vec2(player->getSpeed(), 0.0f));
					}
				}
			}
		}

		a = nullptr;
		b = nullptr;
		player = nullptr;
		//Collision
		return true;
	}

	a = nullptr;
	b = nullptr;
	player = nullptr;

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

Direction CollisionManager::findCollisionDirection(GameObjectV2& a, GameObjectV2& b)
{
	float object_a_bot = a.GetPosition().y + a.GetSize().y;
	float object_a_right = a.GetPosition().x + a.GetSize().x;
	float object_b_bot = b.GetPosition().y + b.GetSize().y;
	float object_b_right = b.GetPosition().x + b.GetSize().x;
	
	float top_collision = object_a_bot - b.GetPosition().y;
	float left_collision = object_a_right - b.GetPosition().x;
	float bottom_collision = object_b_bot - a.GetPosition().y;
	float right_collision = object_b_right - a.GetPosition().x;

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
