#include "PlayerV2.h"
#include "Input_Manager.h"
#include "Collision_Manager.h"
#include "Game_Controller.h"

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
	jumpStrength = -1000.0f;
}

PlayerV2::~PlayerV2()
{

}

bool PlayerV2::Update()
{
	ProcessInput();
	climb();
	oneWayPlatformMove();

	for (auto go : GameDataV2::go_list)
	{
		if (go->getTag() == "Conveyor Platform")
		{
			if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
			{
				conveyor(direction);
			}
		}
		else if (go->getTag() == "Jump Platform")
		{
			if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
			{
				OnJump();
			}
		}
	}


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
			if (!(grounded && (key.first == 's' || key.first == 'S')))
			{
				movement = true;
				key.second();
			}
		}
	}

	for (auto key : KeyBindsPress)
	{
		if (GameDataV2::inputManager->getKeyDown(key.first))
		{
			if (!(grounded && (key.first == 's' || key.first == 'S')))
			{
				movement = true;
				key.second();
			}
		}
	}

	if (!movement)
	{
		move_direction = Direction::NONE;
		key_down = false;
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
				}
			}
		}
	}
}

void PlayerV2::OnMove(Vec2 _direction)
{
	for (auto go : GameDataV2::go_list)
	{
		if (go->getTag() == "Player")
		{
		}
		else if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
		{
			if (go->getTag() == "Slow Platform")
			{
				position += _direction * 0.25;
			}
			else if (go->getTag() == "Speed Platform")
			{
				position += _direction * 1.75;
			}
			else
			{
				position += _direction;
			}
		}
		
		if (!key_down)
		{
			if (_direction.x > 0)
			{
				move_direction = Direction::RIGHT;
				key_down = true;
			}
			else if (_direction.x < 0)
			{
				move_direction = Direction::LEFT;
				key_down = true;
			}
			else if (_direction.y < 0)
			{
				move_direction = Direction::TOP;
				key_down = true;
			}
			else if (_direction.y > 0)
			{
				move_direction = Direction::BOTTOM;
				key_down = true;
			}
		}
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

void PlayerV2::oneWayPlatformMove()
{
	for (auto go : GameDataV2::go_list)
	{
		if (GameDataV2::collsion_manager->getCollisionDirection() != Direction::TOP &&
			GameDataV2::collsion_manager->oneWayPlatform(go->getName()))
		{
			one_way_plat_move = true;
		}
	}

	if (one_way_plat_move && grounded && !climbing)
	{
		OnMove(Vec2(0.0f, -speed));
	}

	if (!grounded && one_way_plat_move)
	{
		one_way_plat_move = false;
	}
}
//Pass true for left, false for right
void PlayerV2::conveyor(bool _left)
{
	direction = _left;

	if (direction)
	{
		OnMove(Vec2(-speed * 0.25, 0.0f));
	}
	else if (!direction)
	{
		OnMove(Vec2(speed * 0.25, 0.0f));
	}

}
