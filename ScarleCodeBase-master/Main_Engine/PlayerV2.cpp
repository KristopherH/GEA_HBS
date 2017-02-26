#include "PlayerV2.h"
#include "Input_Manager.h"

PlayerV2::PlayerV2(Sprite* _sprite, std::string _name, std::string _tag)
	:GameObjectV2(_sprite, _name, _tag)
{
	SetScale(new Vec2(0.5f, 1.5f));
	//Load keybinds from file into list
	KeyBindsPress['_'] = std::bind(&PlayerV2::OnJump, this);
	KeyBindsHold['a'] = std::bind(&PlayerV2::OnMove, this, Vec2(-0.1f, 0.0f));
	KeyBindsHold['d'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.1f, 0.0f));
	//KeyBinds['w'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, -0.1f));
	KeyBindsHold['s'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, 0.1f));
	jumpStrength = -1.0f;
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
	GameDataV2::inputManager->readKeyboard();
	for (auto key : KeyBindsHold)
	{
		if (GameDataV2::inputManager->getKeyHeld(key.first))
		{
			key.second();
		}

	}

	for (auto key : KeyBindsPress)
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