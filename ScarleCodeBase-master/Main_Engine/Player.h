#pragma once
//C++
#include <map>
#include <functional>

//DXTK

//OURS
#include "GameObject.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "SoundManager.h"


class Player : public GameObject
{
public:
	Player() = default;
	Player(Sprite* _sprite, std::string _name, std::string _tag);
	~Player();

	bool Update(float dt) override;

	void ProcessInput();

	void OnJump();
	void OnMove(Vec2);
	void climb();
	void conveyor(bool _left);

	int getScore() { return score; };
	int getLives() { return lives; };
	void setLives();
	void setScore();
	void setClimbing(bool _climb) { climbing = _climb; }
	void setGrounded(bool _grounded) { grounded = _grounded; }

	float getSpeed();

protected:

	int lives;
	int score;
	float speed;
	float jumpStrength;
	float jumpTime;
	float jumpTimeCounter;
	bool stoppedJumping;
	bool can_jump;
	bool jumping;
	bool jump_platform;
	GameObject* climbable_obj = nullptr;
	bool climbing = false;
	bool key_down = false;
	//bool one_way_plat_move = false;

	//void oneWayPlatformMove(); 
	Inputs input;
	//Input component
	std::map<int, std::function<void()>> KeyBindsHold;
	std::map<int, std::function<void()>> KeyBindsPress;
};