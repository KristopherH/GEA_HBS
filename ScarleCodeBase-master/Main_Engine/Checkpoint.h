#pragma once
#include "EditableGameObject.h"
#include "SimpleMath.h"

class Checkpoint : public EditableGameObject
{
public:
	Checkpoint(Sprite* _sprite, Vec2 _pos = Vec2(0.0f, 0.0f), Vec2 _size = Vec2(100.0f, 100.0f), float _rotation = 0.0f, std::string _name = "Checkpoint");
	~Checkpoint() = default;

	bool Update(float dt) override;

private:
	bool active = false;
};

