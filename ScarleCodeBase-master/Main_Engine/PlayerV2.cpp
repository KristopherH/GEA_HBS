#include "PlayerV2.h"

PlayerV2::PlayerV2(Sprite* _sprite)
	:GameObjectV2(_sprite)
{
	//Load keybinds from file into list
	KeyBinds['_'] = std::bind(&PlayerV2::OnJump, this);
	KeyBinds['a'] = std::bind(&PlayerV2::OnMove, this, Vec2(1.0f, 0.0f));
	KeyBinds['d'] = std::bind(&PlayerV2::OnMove, this, Vec2(-1.0f, 0.0f));
	KeyBinds['w'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, 1.0f));
	KeyBinds['s'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, -1.0f));
}

PlayerV2::~PlayerV2()
{

}

bool PlayerV2::Update()
{
	ProcessInput();
	return false;
}

void PlayerV2::ProcessInput()
{
	for (auto key : KeyBinds)
	{
		if (GameDataV2::inputManager->getKeyDown(key.first))
		{
			key.second();
		}

	}
}

void PlayerV2::OnJump()
{
	position += Vec2(0.0f, jumpStrength);
}

void PlayerV2::OnMove(Vec2 _direction)
{
	position += _direction * speed;
}