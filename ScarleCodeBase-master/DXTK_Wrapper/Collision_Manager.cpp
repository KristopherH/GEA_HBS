#include "Collision_Manager.h"
#include "GameObjectV2.h"
bool CollisionManager::boxCollision(GameObjectV2& a, GameObjectV2& b)
{
	if (a.GetPosition().x < b.GetPosition().x + b.GetSize().x &&
		a.GetPosition().x + a.GetSize().x > b.GetPosition.x() &&
		a.GetPosition().y < b.GetPosition().y + b.GetSize().y &&
		a.GetPosition().y + a.GetSize().y > b.GetPosition().y)
	{
		return true;
	}
	return false;
}

bool CollisionManager::circleCollision(GameObjectV2& a, GameObjectV2& b)
{
	return false;
}
