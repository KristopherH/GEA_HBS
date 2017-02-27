#pragma once
#include <string>

class GameObjectV2;

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	bool boxCollision(std::string a_name, std::string b_name);
	bool circleCollision(std::string a_name, std::string b_name);
	bool bitMapCollision(std::string a_name, std::string b_name);
};