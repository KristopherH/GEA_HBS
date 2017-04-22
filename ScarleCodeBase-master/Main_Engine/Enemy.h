#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "GameObject.h"
#include "Player.h"
#include "CustomMath.h"

class Enemy : public GameObject
{
public:
	Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints);
	Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints);
	~Enemy();

	bool Update(float dt) override;

private:
	Player* player;
	std::vector<Vec2> waypoints;
	std::vector<Vec2>::iterator current_waypoint;
};