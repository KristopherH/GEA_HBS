#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "EditableGameObject.h"
#include "CustomMath.h"

class Enemy : public EditableGameObject
{
	friend class EnemyWaypoint;
	friend class LevelLoader;
public:
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints);
	~Enemy();

	bool Update(float dt) override;
	bool Draw() override;

	virtual void toggleEditing() override;

	void addWaypoint();
	void removeWaypoint();

private:
	std::vector<Vec2> waypoints;
	int current_waypoint;
};