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

	void stickyPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY);
	void speedPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY);
	void slowPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY);
	void conveyorPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY);

	GameObjectV2* GetStkPlat() { return platform1; }
	GameObjectV2* GetSpdPlat() { return platform2; }
	GameObjectV2* GetSlwPlat() { return platform3; }
	GameObjectV2* GetCnvyrPlat() { return platform4; }

	~Platforms() = default;

private:
	Sprite* stk_plat;
	Sprite* spd_plat;
	Sprite* slw_plat;
	Sprite* cnvyr_plat;

	GameObjectV2* platform1;
	GameObjectV2* platform2;
	GameObjectV2* platform3;
	GameObjectV2* platform4;
};