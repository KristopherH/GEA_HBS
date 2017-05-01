#pragma once
//C++

//DXTK

//OURS
#include "EditableGameObject.h"

class Collectible : public EditableGameObject
{
public:
	Collectible(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	~Collectible() = default;

	bool Update(float dt) override;
};