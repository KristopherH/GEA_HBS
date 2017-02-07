#pragma once

class GameObject;
class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	bool boxCollision(GameObject& a, GameObject& b);
	bool circleCollision(GameObject& a, GameObject& b);
	bool bitMapCollision(GameObject& a, GameObject& b);
};