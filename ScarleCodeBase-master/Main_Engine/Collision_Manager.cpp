#include "Collision_Manager.h"
//C++
#include <string>

//DXTK

//OURS
#include "Game_Controller.h"
#include "Player.h"
#include "BaseCamera.h"
#include "GameData.h"
#include "Texture.h"

Direction CollisionManager::col_direction = Direction::NONE;

bool CollisionManager::boxCollision(std::string a_name, std::string b_name)
{
	int a_location = GameData::game_controller->getGameObjectLocation(a_name);
	int b_location = GameData::game_controller->getGameObjectLocation(b_name);

	if (a_location == -1 || b_location == -1)
	{
		//OutputDebugString("One or both of the game objects searched for do not exist\n");
		return false;
	}

	GameObject* a = GameData::go_list->at(a_location);
	GameObject* b = GameData::go_list->at(b_location);

	if (!a->getAlive() || !b->getAlive() || !a->getSprite() || !b->getSprite())
	{
		return false;
	}

	Player* player = nullptr;
	BaseCamera* camera = nullptr;
	GameObject* other = nullptr;

	if (a->getTag() == "Player")
	{
		player = static_cast<Player*>(a);
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
		player = static_cast<Player*>(b);
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

	if (a.minCorner.x < b.maxCorner.x &&
		a.maxCorner.x > b.minCorner.x &&
		a.minCorner.y < b.maxCorner.y &&
		a.maxCorner.y > b.minCorner.y)
	{
		findCollisionDirection(&a, &b);
		return true;
	}

	return false;
}


bool CollisionManager::mouseCollision(std::string name)
{
	int obj_location = GameData::game_controller->getGameObjectLocation(name);

	if (obj_location == -1)
	{
		//OutputDebugString("One or both of the game objects searched for do not exist\n");
		return false;
	}

	GameObject* obj = GameData::go_list->at(obj_location);

	if (obj->getBox().Contains(Vec2((float)GameData::inputManager->mouse_x, (float)GameData::inputManager->mouse_y)))
		return true;

	return false;
}



bool CollisionManager::mouseCollision(Rect box)
{
	//float mouse_world_x = (float)GameData::inputManager->mouse_x - ((float)GameData::currentCamera->getPosition().x + ((float)GameData::currentCamera->getCameraSize().x/2));
	//float mouse_world_y = (float)GameData::inputManager->mouse_y - ((float)GameData::currentCamera->getPosition().y + ((float)GameData::currentCamera->getCameraSize().y/2));

	if (box.Contains(Vec2(InputManager::mouse_world_x, InputManager::mouse_world_y)))
		return true;

	return false;
}



bool CollisionManager::bitMapCollision(GameObject& a, GameObject& b)
{
	Rect box;

	box.minCorner.x = max(a.getBox().minCorner.x, b.getBox().minCorner.x);
	box.minCorner.y = max(a.getBox().minCorner.y, b.getBox().minCorner.y);
	box.maxCorner.x = min(a.getBox().maxCorner.x, b.getBox().maxCorner.x);
	box.maxCorner.y = min(a.getBox().maxCorner.y, b.getBox().maxCorner.y);

	if ((box.maxCorner.x < box.minCorner.x && box.maxCorner.y < box.minCorner.y))
	{
		return false;
	}

	for (int h = box.minCorner.y; h < box.maxCorner.y; h++)
	{
		for (int w = box.minCorner.x; w < box.maxCorner.x; w++)
		{
			Vec2 a_new = globalToLocalPos(&a, Vec2(w, h));
			Vec2 b_new = globalToLocalPos(&b, Vec2(w, h));
			if (!a.isTransparent(a_new) && !b.isTransparent(b_new))
			{
				return true;
			}
		}
	}
	return false;
}

Vec2* CollisionManager::getClosestSideBitmap(GameObject& a, GameObject& b)
{
	Rect box;

	box.minCorner.x = max(a.getBox().minCorner.x, b.getBox().minCorner.x);
	box.minCorner.y = max(a.getBox().minCorner.y, b.getBox().minCorner.y);
	box.maxCorner.x = min(a.getBox().maxCorner.x, b.getBox().maxCorner.x);
	box.maxCorner.y = min(a.getBox().maxCorner.y, b.getBox().maxCorner.y);
	if ((box.maxCorner.x < box.minCorner.x && box.maxCorner.y < box.minCorner.y))
	{
		return new Vec2(0.0f, 0.0f);
	}
	Rect blob(Vec2(MAXINT, MAXINT), Vec2(-MAXINT, -MAXINT));

	Rect secondBlob(Vec2(MAXINT, MAXINT), Vec2(-MAXINT, -MAXINT));
	for (int h = box.minCorner.y; h < box.maxCorner.y; h++)
	{
		for (int w = box.minCorner.x; w < box.maxCorner.x; w++)
		{
			Vec2 a_new = globalToLocalPos(&a, Vec2(w, h));
			Vec2 b_new = globalToLocalPos(&b, Vec2(w, h));
			if (!a.isTransparent(a_new) && !b.isTransparent(b_new))
			{
				blob.maxCorner.x = max(blob.maxCorner.x, w);
				blob.maxCorner.y = max(blob.maxCorner.y, h);
				blob.minCorner.x = min(blob.minCorner.x, w);
				blob.minCorner.y = min(blob.minCorner.y, h);
			}
			if (!b.isTransparent(b_new))
			{
				secondBlob.maxCorner.x = max(secondBlob.maxCorner.x, w);
				secondBlob.maxCorner.y = max(secondBlob.maxCorner.y, h);
				secondBlob.minCorner.x = min(secondBlob.minCorner.x, w);
				secondBlob.minCorner.y = min(secondBlob.minCorner.y, h);
			}
		}
	}
	//desired - current
	//Vec2 direction(blob.Center() - Vec2(0.0f, 1.0f));
	//Vec2 direction(blob.Center() - Vec2(0.0f, -1.0f));
	//Vec2 direction(blob.Center() - Vec2(1.0f, 0.0f));
	//Vec2 direction(blob.Center() - Vec2(-1.0f, 0.0f));
	//
	if (abs(blob.minCorner.x - blob.maxCorner.x) < abs(blob.minCorner.y - blob.maxCorner.y)
		&& abs(blob.minCorner.x - blob.maxCorner.x) < abs(blob.maxCorner.y - blob.minCorner.y))
	{
		if (abs(blob.minCorner.x - blob.maxCorner.x) < abs(blob.maxCorner.x - blob.minCorner.x))
		{
			Vec2* sideDistance = new Vec2(blob.minCorner.x - blob.maxCorner.x, 0.0f);
			return sideDistance;
		}
		else
		{
			Vec2* sideDistance = new Vec2(blob.maxCorner.x - blob.minCorner.x, 0.0f);
			return sideDistance;
		}
	}
	else
	{
		if (abs(blob.minCorner.y - blob.maxCorner.y) < abs(blob.maxCorner.y - blob.minCorner.y))
		{
			Vec2* sideDistance = new Vec2(0.0f, -(blob.minCorner.y - blob.maxCorner.y));
			return sideDistance;
		}
		else
		{
			Vec2* sideDistance = new Vec2(0.0f, -(blob.maxCorner.y - blob.minCorner.y));
			return sideDistance;
		}
	}
}

#pragma region in the way
Direction CollisionManager::getCollisionDirection()
{
	return col_direction;
}

bool CollisionManager::oneWayPlatform(std::string a_name)
{
	if (a_name == "Camera")
		return false;

	int a_location = GameData::game_controller->getGameObjectLocation(a_name);
	int player_location = GameData::game_controller->getGameObjectLocation("Player");

	if (a_location == -1 || player_location == -1)
	{
		//OutputDebugString("One or both of the game objects searched for do not exist");
		return false;
	}

	GameObject* a = GameData::go_list->at(a_location);
	GameObject* player = GameData::go_list->at(player_location);

	if (player->getPosition().y > a->getPosition().y + a->getSize().y ||
		player->getPosition().y + player->getSize().y < a->getPosition().y)
	{
		return true;
	}

	return false;
}



Direction CollisionManager::findCollisionDirection(GameObject* a, GameObject* b)
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

	object_a_bot = a->maxCorner.y;
	object_a_right = a->maxCorner.x;
	object_b_bot = b->maxCorner.y;
	object_b_right = b->maxCorner.x;

	top_collision = object_a_bot - b->minCorner.y;
	left_collision = object_a_right - b->minCorner.x;
	bottom_collision = object_b_bot - a->minCorner.y;
	right_collision = object_b_right - a->minCorner.x;

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
#pragma endregion
Vec2 CollisionManager::globalToLocalPos(GameObject * obj, Vec2 global_pos)
{
	int x = obj->getBox().minCorner.x;
	int y = obj->getBox().minCorner.y;

	Vec2 local_pos;
	local_pos.x = global_pos.x - x;
	local_pos.y = global_pos.y - y;

	Vec2 pixelPos;
	Vec2 boxSize(obj->getBox().maxCorner - obj->getBox().minCorner);
	pixelPos.x = (int)((local_pos.x * ((boxSize.x-1) / obj->getScale().x)) / boxSize.x);
	pixelPos.y = (int)((local_pos.y * ((boxSize.y-1) / obj->getScale().y)) / boxSize.y);

	//// translate point to origin
	//float tempX = pixelPos.x - (boxSize.x / 2);
	//float tempY = pixelPos.y - (boxSize.y / 2);

	//// now apply rotation
	//float rotatedX = tempX*cos(obj->getRotation()) - tempY*sin(obj->getRotation());
	//float rotatedY = tempX*sin(obj->getRotation()) + tempY*cos(obj->getRotation());

	//// translate back
	//pixelPos.x = rotatedX + (boxSize.x / 2);
	//pixelPos.y = rotatedY + (boxSize.y / 2);

	return pixelPos;
}
