#include "GameObjectV2.h"
#include "Input_Manager.h"

GameObjectV2::GameObjectV2(Sprite* _sprite, InputManager* _input_component)
	:sprite(_sprite), input_component(_input_component)
{
}

GameObjectV2::~GameObjectV2()
{
	delete sprite;
	sprite = nullptr;
}

bool GameObjectV2::Update()
{
	if (input_component)
	{
		keyboardUpdate();
		return true;
	}

	return false;
}

bool GameObjectV2::keyboardUpdate()
{
	input_component->readKeyboard();

	if (input_component->getKeyHeld(201))
	{
		movePosition(new Vec2(5, 0));
	}

	return true;

}

void GameObjectV2::movePosition(Vec2* _translation)
{
	position.x += _translation->x;
	position.y += _translation->y;
}