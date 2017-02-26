#include "PlayerV2.h"
#include "Input_Manager.h"
#include "Collision_Manager.h"

PlayerV2::PlayerV2(Sprite* _sprite, std::string _name, std::string _tag)
	:GameObjectV2(_sprite, _name, _tag)
{
	SetScale(new Vec2(0.5f, 1.5f));
	//Load keybinds from file into list
	KeyBindsPress['_'] = std::bind(&PlayerV2::OnJump, this);
	KeyBindsHold['a'] = std::bind(&PlayerV2::OnMove, this, Vec2(-speed, 0.0f));
	KeyBindsHold['d'] = std::bind(&PlayerV2::OnMove, this, Vec2(speed, 0.0f));
	KeyBindsHold['w'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, -speed));
	KeyBindsHold['s'] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, speed));
	jumpStrength = -1.0f;
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
	bool movement = false;
	GameDataV2::inputManager->readKeyboard();
	for (auto key : KeyBindsHold)
	{
		if (GameDataV2::inputManager->getKeyHeld(key.first))
		{
			movement = true;

			if (grounded && (key.first == 's' || key.first == 'S'))
			{
				return;
			}

			key.second();
		}

	}

	for (auto key : KeyBindsPress)
	{
		if (GameDataV2::inputManager->getKeyDown(key.first))
		{
			movement = true;
			key.second();
		}

	}

	if (!movement)
	{
		move_direction = Direction::NONE;
	}
}

void PlayerV2::OnJump()
{
	position += Vec2(0.0f, jumpStrength);
}

void PlayerV2::OnMove(Vec2 _direction)
{
	position += _direction;

	if (_direction.x > 0)
	{
		move_direction = Direction::RIGHT;
	}
	else if (_direction.x < 0)
	{
		move_direction = Direction::LEFT;
	}
	else if (_direction.y > 0)
	{
		move_direction = Direction::TOP;
	}
	else if (_direction.y < 0)
	{
		move_direction = Direction::BOTTOM;
	}
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
		climable_name = "NULL";
	}
}

float PlayerV2::getSpeed()
{
	return speed;
}
