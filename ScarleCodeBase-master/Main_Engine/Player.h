#pragma once
//C++
#include <map>
#include <functional>

//DXTK

//OURS
#include "GameObject.h"
#include "GameData.h"
#include "Input_Manager.h"


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
	int getLives() { return lives; };
	void setLives();

	float getSpeed();

protected:

	int lives;
	float speed;
	float jumpStrength;
	float jumpTime;
	float jumpTimeCounter;
	bool stoppedJumping;
	bool can_jump;
	bool jumping;
	bool jump_platform;
	std::string Climbable_name = "NULL";
	bool climbing = false;
	bool key_down = false;
	//bool one_way_plat_move = false;

	//void oneWayPlatformMove(); 
	Inputs input;
	//Input component
	std::map<int, std::function<void()>> KeyBindsHold;
	std::map<int, std::function<void()>> KeyBindsPress;
};