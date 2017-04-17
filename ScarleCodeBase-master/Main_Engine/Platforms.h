#pragma once
//C++
#include <map>
#include <string>

//DXTK

//OURS
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "Sprite.h"
#include "Player.h"
#include "GameData.h"
#include "GameObject.h"
#include "Texture.h"


class Platforms
{
public:
	Platforms() = delete;
	Platforms(Renderer* _renderer);
	~Platforms() = default;

	GameObject* standardPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObject* stickyPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObject* speedPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObject* slowPlatform(float x, float y, float sizeX, float sizeY, string name);
	GameObject* conveyorPlatform(float x, float y, float sizeX, float sizeY, string name, bool leftOrRight);
	GameObject* jumpPlatform(float x, float y, float sizeX, float sizeY, string name);

	static std::map<std::string, Texture*> platform_sprites;

private:
	//Sprite* spr = nullptr;
	GameObject* platform = nullptr;
};