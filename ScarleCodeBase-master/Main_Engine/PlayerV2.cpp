#include "PlayerV2.h"
#include "Input_Manager.h"
#include "Collision_Manager.h"

PlayerV2::PlayerV2(Sprite* _sprite, std::string _name, std::string _tag)
	:GameObjectV2(_sprite, _name, _tag)
{
	SetScale(new Vec2(0.5f, 1.5f));
	//Load keybinds from file into list
	KeyBindsPress['_'] = std::bind(&PlayerV2::OnJump, this);
	KeyBindsHold['a'] = std::bind(&PlayerV2::OnMove, this, Vec2(-0.5f, 0.0f));
	KeyBindsHold['d'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.5f, 0.0f));
	KeyBindsHold['w'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, -0.5f));
	KeyBindsHold['s'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, 0.5f));
	jumpStrength = -20.0f;
}

PlayerV2::~PlayerV2()
{

}

bool PlayerV2::Update()
{
	ProcessInput();
	climb();

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
	if (gravity_on)
	{
		for (auto go : GameDataV2::go_list)
		{
			if (go->getTag() == "Sticky Platform")
			{
				if (!GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
				{
					position += Vec2(0.0f, jumpStrength);
					climable_name = go->getName();
				}
			}
		}
	}
	else
	{
	}
}

void PlayerV2::OnMove(Vec2 _direction)
{
	position += _direction * speed;
}

void PlayerV2::climb()
{
	if (gravity_on)
	{
		for (auto go : GameDataV2::go_list)
		{
			if (go->getTag() == "Climable")
			{
				if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
				{
					climbing = true;
					gravity_on = false;
					climable_name = go->getName();
				}
			}
		}
	}

	if (!GameDataV2::collsion_manager->boxCollision(this->name, climable_name))
	{
		climbing = false;
		gravity_on = true;
	}
}
