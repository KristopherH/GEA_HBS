#pragma once
#include "GameObjectV2.h"

class Enemy : public GameObjectV2
{
public:
	Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Enemy(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	~Enemy();

private:

};