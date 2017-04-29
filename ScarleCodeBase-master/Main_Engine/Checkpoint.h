#pragma once
#include "GameObject.h"
#include "SimpleMath.h"

class Checkpoint : public GameObject
{
public:
	Checkpoint(Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	Checkpoint(Sprite* _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name);
	~Checkpoint() = default;

	bool Update(float dt) override;

private:
	bool active = false;
};

