#pragma once
#include <string>
#include "Enum_container.h"

class GameObjectV2;

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	bool boxCollision(std::string a_name, std::string b_name);
	bool circleCollision(std::string a_name, std::string b_name);
	bool bitMapCollision(std::string a_name, std::string b_name);
	Direction getCollisionDirection();

private:
	Direction findCollisionDirection(GameObjectV2& a, GameObjectV2& b);
	Direction col_direction = Direction::NONE;
};