#pragma once
//C++

//DXTK

//OURS
#include "GameObjectV2.h"

class Collectible : public GameObjectV2
{
public:
	Collectible(Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Collectible(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	~Collectible();

	bool Update() override;
};