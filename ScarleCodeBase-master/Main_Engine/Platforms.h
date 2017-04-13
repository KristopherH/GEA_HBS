#pragma once
//C++
#include <map>
#include <string>

//DXTK

//OURS
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "Sprite.h"
#include "PlayerV2.h"
#include "GameDataV2.h"
#include "GameObjectV2.h"


class Platforms : public Sprite
{
public:
	Platforms() = delete;
	Platforms(Renderer* _renderer);
	~Platforms() = default;

	GameObjectV2* standardPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* stickyPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* speedPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* slowPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* conveyorPlatform(float x, float y, float sizeX, float sizeY, string name, bool leftOrRight);
	GameObjectV2* jumpPlatform(float x, float y, float sizeX, float sizeY, string name);


private:
	std::map<std::string, Sprite*> platform_sprites;
	Sprite* spr = nullptr;
	GameObjectV2* platform = nullptr;
};