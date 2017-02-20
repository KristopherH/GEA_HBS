#include "GameObjectV2.h"

GameObjectV2::GameObjectV2(Sprite* _sprite)
	:sprite(_sprite)
{
}

GameObjectV2::~GameObjectV2()
{
	delete sprite;
	sprite = nullptr;
}

bool GameObjectV2::Update()
{
	return false;
}
