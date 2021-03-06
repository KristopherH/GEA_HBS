#pragma once
#include "GameObject.h"

class Enemy;

class EnemyWaypoint : public GameObject
{
public:
	EnemyWaypoint(Enemy* _parent, int _index);
	~EnemyWaypoint();

	virtual bool Update(float dt) override;

	void setPosition(Vec2* _position) override;
	void movePosition(Vec2* _translation) override;

	Enemy* parent;
	int index;
};