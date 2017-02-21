#pragma once
#include "GameObjectV2.h"

class PlayerV2 : public GameObjectV2
{
public:
	PlayerV2(Sprite* _sprite, void* _controller);
	~PlayerV2();

	bool Update() override;

protected:

	int lives;

	//Input component
	void* controller;
};