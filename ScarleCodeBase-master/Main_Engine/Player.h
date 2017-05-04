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
	Player(Sprite* _sprite, std::string _name, std::string _tag, int _sprites_across = 1, int _sprites_down = 1);
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
	bool pauseSetUp = false;
	std::map<int, std::function<void()>> KeyBindsHold;
	std::map<int, std::function<void()>> KeyBindsPress;
};