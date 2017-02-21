#include "GameObjectV2.h"
#include "Input_Manager.h"

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

void GameObjectV2::movePosition(Vec2* _translation)
{
	position.x += _translation->x;
	position.y += _translation->y;
}