#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "GameObject.h"
#include "CustomMath.h"

class Enemy : public GameObject
{
	friend class EnemyWaypoint;
	friend class LevelLoader;
public:
	Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints);
	Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints);
	~Enemy();

	bool Update(float dt) override;
	bool Draw() override;

	void toggleWaypoints();

	void addWaypoint();
	void removeWaypoint();

private:
	std::vector<Vec2> waypoints;
	int current_waypoint;
	std::vector<EnemyWaypoint*> waypointsGOs;
	bool displayWaypoints = false;
};