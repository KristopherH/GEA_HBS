#pragma once
#include <string>
#include "Enum_container.h"
#include "CustomMath.h"

class GameObjectV2;

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	bool boxCollision(std::string a_name, std::string b_name);
	bool boxCollision(Rect a, Rect b);
	bool circleCollision(std::string a_name, std::string b_name);
	bool bitMapCollision(std::string a_name, std::string b_name);
	Direction getCollisionDirection();
	bool oneWayPlatform(std::string a_name);

private:
	Direction findCollisionDirection(GameObjectV2* a, GameObjectV2* b);
	Direction findCollisionDirection(Rect * a, Rect * b);
	Direction col_direction = Direction::NONE;
};