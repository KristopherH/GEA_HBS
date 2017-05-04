#pragma once
//C++
#include <string>

//DXTK

//OURS
#include "Enum_container.h"
#include "../DXTK_Wrapper/CustomMath.h"

class GameObject;

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	static bool boxCollision(std::string a_name, std::string b_name);
	static bool boxCollision(Rect a, Rect b);
	//static bool boxCollisionOA(Rect a, Rect b);
	//static bool boxCollisionOA(GameObject * a, GameObject * b);
	static bool mouseCollision(std::string name);
	static bool mouseCollision(Rect box);
	static bool bitMapCollision(GameObject& a, GameObject& b); //GET TO IT
	Vec2* getClosestSideBitmap(GameObject & a, GameObject & b);
	static Direction getCollisionDirection();
	static bool oneWayPlatform(std::string a_name);

private:
	static Direction findCollisionDirection(GameObject* a, GameObject* b);
	static Direction findCollisionDirection(Rect * a, Rect * b);
	static Vec2 globalToLocalPos(GameObject* obj, Vec2 global_pos);
	static Direction col_direction;
};