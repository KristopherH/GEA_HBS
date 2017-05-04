#include "Player.h"
//C++
#include <iostream>

//DXTK

//OURS
#include "Input_Manager.h"
#include "Collision_Manager.h"
#include "Game_Controller.h"
#include "SceneManager.h"
#include "PauseMenu.h"
#include "GameOver.h"

Player::Player(Sprite* _sprite, std::string _name, std::string _tag)
	:GameObject(_sprite, _name, _tag)
{
	playerr = true;
	animated = true;
	setScale(new Vec2(0.5f, 1.5f));
	jumpStrength = -0.04f;
	speed = 0.02f;
	lives = 5;
	score = 0;
	jumpTime = 0.2f;
	jumpTimeCounter = jumpTime;
	//Load keybinds from file into list

	#ifndef ARCADE
	std::cout << "Arcade not defined" << std::endl;
	#endif

	//KeyBindsHold[] = std::bind(&Player::OnJump, this);
	KeyBindsHold[InputManager::key_inputs[InputLabel::LEFT]] = std::bind(&Player::OnMove, this, Vec2(-speed, 0.0f));
	KeyBindsHold[InputManager::key_inputs[InputLabel::RIGHT]] = std::bind(&Player::OnMove, this, Vec2(speed, 0.0f));
	KeyBindsHold[InputManager::key_inputs[InputLabel::UP]] = std::bind(&Player::OnMove, this, Vec2(0.0f, -speed));
	KeyBindsHold[InputManager::key_inputs[InputLabel::DOWN]] = std::bind(&Player::OnMove, this, Vec2(0.0f, speed));
	KeyBindsHold[InputManager::key_inputs[InputLabel::PAUSE]] = std::bind(&Player::PauseGame, this);
}

Player::~Player()
{

}

bool Player::Update(float dt)
{
	jumping = false;
	if (grounded)
	{
		//the jumpcounter is whatever we set jumptime to in the editor.
		jumpTimeCounter = jumpTime;
		jump_platform = false;
	}
	can_jump = true;
	for (auto go : *GameData::go_list)
	{
		if (go->getTag() == "ConveyorLeft" || go->getTag() == "ConveyorRight")
		{
			if (GameData::collsion_manager->boxCollision(this->box, go->getBox()))
			{
				if (go->getTag() == "ConveyorLeft") conveyor(true);
				else if (go->getTag() == "ConveyorRight") conveyor(false);
			}
		}
		else if (go->getTag() == "JumpPlatform")
		{
			if (GameData::collsion_manager->boxCollision(this->box, go->getBox()))
			{
				jump_platform = true;
			}
		}
		else if (go->getTag() == "StickyPlatform")
		{
			if (GameData::collsion_manager->boxCollision(this->box, go->getBox()))
			{
				//prevent jumping
				can_jump = false;
				stoppedJumping = true;
			}
		}
	}
	if (jump_platform)
	{
		OnJump(dt);
	}
	if (GameData::inputManager->getKeyHeld(InputManager::key_inputs[InputLabel::JUMP]))
	{
		OnJump(dt);
	}
	ProcessInput();
	if (climbing && !stoppedJumping && velocity.y <= 0)
	{
		stoppedJumping = true;
		gravity_on = true;
	}

	if (velocity.y >= 0.1f || velocity.y <= -0.01f && !climbing && sprite->getAnimationState() == AnimationState::IDLE)
	{
		sprite->setAnimationState(AnimationState::JUMP);
	}
	else if (velocity.x >= 0.1f || velocity.x <= -0.01f && sprite->getAnimationState() == AnimationState::IDLE)
	{
		sprite->setAnimationState(AnimationState::WALK);
	}
	else if(sprite->getAnimationState() != AnimationState::IDLE && velocity.y <= 0.1f && velocity.y >= -0.01f && velocity.x <= 0.1f && velocity.x >= -0.01f)
	{
		sprite->setAnimationState(AnimationState::IDLE);
	}
	GameObject::Update(dt);
	climb();
	return false;
}

void Player::gravityUpdate()
{
	bool new_grounded = false;
	for (auto other : *GameData::go_list)
	{
		if (this != other && other->getSolid())
		{
			if (GameData::collsion_manager->boxCollision(
				this->box, other->getBox()))
			{
				if (velocity.y >= 0.0f || !(other->getPassThruBottom()))
				{
					if (GameData::collsion_manager->bitMapCollision(*this, *other))
					{
						position += *(GameData::collsion_manager->getClosestSideBitmap(*this, *other));
						if (!grounded) // If not previously grounded
						{
							velocity.y = 0.0f;
							acceleration.y = 0.0f;
						}

						new_grounded = true;
						break;
					}
				}
			}
		}
		if (new_grounded)
		{
			break;
		}
	}

	grounded = new_grounded;

	if (!grounded && gravity_on)
	{
		acceleration.y += gravity_constant;
	}
}

void Player::ProcessInput()
{
	bool movement = false;
	for (auto key : KeyBindsHold)
	{
		if (GameData::inputManager->getKeyHeld(key.first))
		{
			movement = true;
			key.second();
		}
	}

	for (auto key : KeyBindsPress)
	{
		if (GameData::inputManager->getKeyDown(key.first))
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

void Player::OnJump(float dt)
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
			GameData::sound_manager->playSound("Jump-SoundEffect.wav");
		}
	
		//if you keep holding down the mouse button...
		if (!stoppedJumping)
		{
			//and your counter hasn't reached zero...
			if (jumpTimeCounter > 0)
			{
				//keep jumping!
				acceleration += Vec2(0.0f, jumpStrength);
           		jumpTimeCounter -= dt;
			}
			else
			{
				int i = 0;
			}
		}
	}
}

void Player::OnMove(Vec2 _direction)
{	
	bool moved = false;
	if (climbing)
	{
		position += _direction * 100;
		return;
	}
	if (_direction.y != 0.0f)
	{
		return;
	}
	for (auto go : *GameData::go_list)
	{
		if (go->getName() == name)
		{

		}
		else if (GameData::collsion_manager->boxCollision(this->box, go->getBox()))
		{
			if (go->getTag() == "SlowPlatform")
			{
				acceleration += _direction * 0.25;
				moved = true;
				break;
			}
			else if (go->getTag() == "SpeedPlatform")
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


void Player::climb()
{
	if (gravity_on)
	{
		for (auto go : (*GameData::go_list))
		{
			if (go->getTag() == "Climbable")
			{
				if (GameData::collsion_manager->boxCollision(this->box, go->getBox()))
				{
					if (!climbing)
					{
						velocity.y = 0.0f;
						acceleration.y = 0.0f;
					}
					climbing = true;
					gravity_on = false;
					grounded = false;
					climbable_obj = go;

				}
			}
		}
	}

	if (climbable_obj)
	{
		if (!GameData::collsion_manager->boxCollision(this->box, climbable_obj->getBox()))
		{
			climbing = false;
			gravity_on = true;
			climbable_obj = nullptr;
		}
	}
}

float Player::getSpeed()
{
	return speed;
}

void Player::PauseGame()
{
	if (pauseSetUp == false)
	{
		GameData::scene_manager->addScene("PauseMenuScene", new PauseMenu());
		pauseSetUp = true;
	}
	GameData::scene_manager->setCurrentScene("PauseMenuScene", false);
	GameData::sound_manager->stopSound();
	GameData::sound_manager->playSound("MainMenu-Music.wav", false, true);
}

//void Player::oneWayPlatformMove()
//{
//	for (auto go : GameData::go_list)
//	{
//		if (GameData::collsion_manager->getCollisionDirection() != Direction::TOP &&
//			GameData::collsion_manager->oneWayPlatform(go->getName()) && !one_way_plat_move)
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
void Player::conveyor(bool _left)
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

void Player::killPlayer()
{
	lives -= 1;
	setPosition(lastCheckpoint);
	if (lives <= 0)
	{
		GameData::scene_manager->addScene("GameOver", new GameOver());
		GameData::scene_manager->setCurrentScene("GameOver");
	}
}

void Player::setScore()
{
	score += 1;
}
