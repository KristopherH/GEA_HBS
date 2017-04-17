#pragma once
//C++
#include <string>

//DXTK

//OURS
#include "Enum_container.h"
#include "CustomMath.h"

class GameObject;

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
	Direction findCollisionDirection(GameObject* a, GameObject* b);
	Direction findCollisionDirection(Rect * a, Rect * b);
	Direction col_direction = Direction::NONE;
};