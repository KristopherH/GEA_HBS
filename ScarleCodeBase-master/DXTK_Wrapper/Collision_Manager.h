#pragma once

class GameObjectV2;
class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	bool boxCollision(GameObjectV2& a, GameObjectV2& b);
	bool circleCollision(GameObjectV2& a, GameObjectV2& b);
	bool bitMapCollision(GameObjectV2& a, GameObjectV2& b);
};