#pragma once
//C++

//DXTK

//OURS
#include "GameObject.h"

class Collectible : public GameObject
{
public:
	Collectible(Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Collectible(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	~Collectible();

	bool Update() override;
};