#pragma once
#include "GameObjectV2.h"
#include "GameDataV2.h"
#include <map>
#include <functional>

class PlayerV2 : public GameObjectV2
{
public:
	PlayerV2() = default;
	PlayerV2(Sprite* _sprite, std::string _name, std::string _tag);
	~PlayerV2();

	bool Update() override;

	void ProcessInput();

	void OnJump();
	void OnMove(Vec2);
	void climb();

	float getSpeed();

protected:

	int lives;
	float speed = 1.0f;
	float jumpStrength;
	std::string climable_name = "NULL";
	bool climbing = false;


	//Input component
	std::map<char, std::function<void()>> KeyBindsHold;
	std::map<char, std::function<void()>> KeyBindsPress;
};