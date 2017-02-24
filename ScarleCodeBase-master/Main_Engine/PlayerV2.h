#pragma once
#include "GameObjectV2.h"
#include "GameDataV2.h"
#include <map>
#include <functional>

class PlayerV2 : public GameObjectV2
{
public:
	PlayerV2(Sprite* _sprite, std::string _name, std::string _tag);
	~PlayerV2();

	bool Update() override;

	void ProcessInput();

	void OnJump();
	void OnMove(Vec2);

protected:

	int lives;
	float speed;
	float jumpStrength;

	//Input component
	std::map<char, std::function<void()>> KeyBinds;
};