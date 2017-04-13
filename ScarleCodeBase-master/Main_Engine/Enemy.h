#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "GameObjectV2.h"
#include "PlayerV2.h"
#include "CustomMath.h"

class Enemy : public GameObjectV2
{
public:
	Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints);
	~Enemy();

	bool Update() override;

private:
	PlayerV2* player;
	std::vector<Vec2> waypoints;
};