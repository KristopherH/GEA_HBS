#include "PlayerV2.h"
//C++
#include <iostream>

//DXTK

//OURS
#include "Input_Manager.h"
#include "Collision_Manager.h"
#include "Game_Controller.h"

PlayerV2::PlayerV2(Sprite* _sprite, std::string _name, std::string _tag)
	:GameObjectV2(_sprite, _name, _tag)
{
	setScale(new Vec2(0.5f, 1.5f));
	jumpStrength = -0.02f;
	speed = 0.01f;
	lives = 3;
	jumpTime = 0.8f;
	jumpTimeCounter = jumpTime;
	//Load keybinds from file into list

	#ifndef ARCADE
	std::cout << "Arcade not defined" << std::endl;
	#endif

	KeyBindsHold[Inputs::JUMP] = std::bind(&PlayerV2::OnJump, this);
	KeyBindsHold[Inputs::LEFT] = std::bind(&PlayerV2::OnMove, this, Vec2(-speed, 0.0f));
	KeyBindsHold[Inputs::RIGHT] = std::bind(&PlayerV2::OnMove, this, Vec2(speed, 0.0f));
	KeyBindsHold[Inputs::UP] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, -speed));
	KeyBindsHold[Inputs::DOWN] = std::bind(&PlayerV2::OnMove, this, Vec2(0.0f, speed));
	
}

PlayerV2::~PlayerV2()
{

}

bool PlayerV2::Update()
{
	jumping = false;
	if (grounded)
	{
		//the jumpcounter is whatever we set jumptime to in the editor.
		jumpTimeCounter = jumpTime;
		jump_platform = false;
	}
	can_jump = true;
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
				jump_platform = true;
			}
		}
		else if (go->getTag() == "Sticky Platform")
		{
			if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
			{
				//prevent jumping
				can_jump = false;
				stoppedJumping = true;
			}
		}
	}
	if (jump_platform)
	{
		OnJump();
	}
	ProcessInput();
	//oneWayPlatformMove();
	if (climbing && !stoppedJumping && velocity.y <= 0)
	{
		stoppedJumping = true;
		gravity_on = true;
	}
	GameObjectV2::Update();
	climb();
	return false;
}

void PlayerV2::ProcessInput()
{
	bool movement = false;

	for (auto key : KeyBindsHold)
	{
		if (GameDataV2::inputManager->getKeyHeld(key.first))
		{
			movement = true;
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
	if (!jumping)
	{
		jumpTimeCounter = 0;
		stoppedJumping = true;
	}
	if (!movement)
	{
		move_direction = Direction::NONE;
		key_down = false;
	}
}

void PlayerV2::OnJump()
{
	if (!can_jump)
	{
		return;
	}
	jumping = true;
	if (gravity_on)
	{
		//and you are on the ground...
		if (grounded)
		{
			
			//position += Vec2(0.0f, jumpStrength);
			acceleration += Vec2(0.0f, jumpStrength);
			stoppedJumping = false;
		}
	
		//if you keep holding down the mouse button...
		if (!stoppedJumping)
		{
			//and your counter hasn't reached zero...
			if (jumpTimeCounter > 0)
			{
				//keep jumping!
				acceleration += Vec2(0.0f, jumpStrength);
           		jumpTimeCounter -= /*detaTime???*/0.01f;
			}
		}
	}
}

void PlayerV2::OnMove(Vec2 _direction)
{
	bool moved = false;
	if (climbing)
	{
		position += _direction *100;
		return;
	}
	if (_direction.y != 0.0f)
	{
		return;
	}
	for (auto go : GameDataV2::go_list)
	{
		if (go->getName() == name)
		{

		}
		else if (GameDataV2::collsion_manager->boxCollision(this->name, go->getName()))
		{
			if (go->getTag() == "Slow Platform")
			{
				acceleration += _direction * 0.25;
				moved = true;
				break;
			}
			else if (go->getTag() == "Speed Platform")
			{
				acceleration += _direction * 3.0;
				moved = true;
				break;
			}
			else
			{
				acceleration += _direction;
				moved = true;
				break;
			}
		}
	}

	if (!moved)
	{
		acceleration += _direction;
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
					if( !climbing)
					{
						velocity.y = 0.0f;
						acceleration.y = 0.0f;
					}
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

//void PlayerV2::oneWayPlatformMove()
//{
//	for (auto go : GameDataV2::go_list)
//	{
//		if (GameDataV2::collsion_manager->getCollisionDirection() != Direction::TOP &&
//			GameDataV2::collsion_manager->oneWayPlatform(go->getName()) && !one_way_plat_move)
//		{
//			one_way_plat_move = true;
//		}
//	}
//
//	if (one_way_plat_move && grounded && !climbing)
//	{
//		//position += Vec2(0.0f, -speed * 2000);
//	}
//
//	if (!grounded && one_way_plat_move)
//	{
//		one_way_plat_move = false;
//	}
//}

//Pass true for left, false for right
void PlayerV2::conveyor(bool _left)
{
	if (_left)
	{
		OnMove(Vec2(-speed * 0.5f, 0.0f));
	}
	else if (!_left)
	{
		OnMove(Vec2(speed * 0.5f, 0.0f));
	}

}

void PlayerV2::setLives()
{
	lives -= 1;
}
