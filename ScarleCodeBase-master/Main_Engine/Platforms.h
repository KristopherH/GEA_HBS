#pragma once

#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "Sprite.h"
#include "PlayerV2.h"
#include "GameDataV2.h"
#include "GameObjectV2.h"

class Platforms : public Sprite
{
public:
	Platforms();

	GameObjectV2* standardPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* stickyPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* speedPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* slowPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name);
	GameObjectV2* conveyorPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name, bool leftOrRight);
	GameObjectV2* jumpPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name);

	~Platforms() = default;

private:
	Sprite* spr = nullptr;
	GameObjectV2* platform = nullptr;
	std::unique_ptr<PlayerV2> player;
};