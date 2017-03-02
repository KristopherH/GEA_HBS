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
	jumpStrength = -25.0f;
	lives = 3;
}

PlayerV2::~PlayerV2()
{

}

bool PlayerV2::Update()
{
	GameObjectV2::Update();
	ProcessInput();
	climb();
	oneWayPlatformMove();

	for (auto go : GameDataV2::go_list)
	{
		if (go->getTag() == "Conveyor Left" || go->getTag() == "Conveyor Right")
		{
			if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
			{
				if (go->getTag() == "Conveyor Left") conveyor(true);
				else if (go->getTag() == "Conveyor Right") conveyor(false);
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
	if (gravity_on && grounded)
	{
		for (auto go : GameDataV2::go_list)
		{
			if (this != go && GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
			{
				if (go->getTag() != "Sticky Platform")
				{
					position += Vec2(0.0f, jumpStrength * 2);
				}
			}
		}
	}
}

void PlayerV2::OnMove(Vec2 _direction)
{
	for (auto go : GameDataV2::go_list)
	{
		if (go->getName() == name)
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
				position += _direction * 3.0;
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
			if (go->getTag() == "Climbable")
			{
				if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
				{
					climbing = true;
					gravity_on = false;
					grounded = false;
					Climbable_name = go->getName();
				}
			}
		}
	}

	if (!GameDataV2::collsion_manager->boxCollision(this->name, Climbable_name))
	{
		climbing = false;
		gravity_on = true;
		Climbable_name = "NULL";
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
			GameDataV2::collsion_manager->oneWayPlatform(go->getName()) && !one_way_plat_move)
		{
			one_way_plat_move = true;
		}
	}

	if (one_way_plat_move && grounded && !climbing)
	{
		OnMove(Vec2(0.0f, -speed * 5));
	}

	if (!grounded && one_way_plat_move)
	{
		one_way_plat_move = false;
	}
}
//Pass true for left, false for right
void PlayerV2::conveyor(bool _left)
{
	_left;

	if (_left)
	{
		OnMove(Vec2(-speed * 0.25, 0.0f));
	}
	else if (!_left)
	{
		OnMove(Vec2(speed * 0.25, 0.0f));
	}

}

void PlayerV2::setLives()
{
	lives -= 1;
}
