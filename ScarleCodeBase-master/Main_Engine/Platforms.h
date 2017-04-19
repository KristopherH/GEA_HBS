#pragma once
//C++
#include <map>
#include <string>

//DXTK
#if defined _DXTK_
#include "..\DXTK_Wrapper\Renderer.h"
#include "..\DXTK_Wrapper\Texture.h"
#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/Renderer.h"
#include "../Phyre/Code/Texture.h"
#endif

//OURS
#include "Sprite.h"
#include "Player.h"
#include "GameData.h"
#include "GameObject.h"

class Platforms
{
public:
	Platforms() = delete;
	Platforms(Renderer* _renderer);
	~Platforms() = default;

	GameObject* standardPlatform(float x, float y, float sizeX, float sizeY, std::string name);
	GameObject* stickyPlatform(float x, float y, float sizeX, float sizeY, std::string name);
	GameObject* speedPlatform(float x, float y, float sizeX, float sizeY, std::string name);
	GameObject* slowPlatform(float x, float y, float sizeX, float sizeY, std::string name);
	GameObject* conveyorPlatform(float x, float y, float sizeX, float sizeY, std::string name, bool leftOrRight);
	GameObject* jumpPlatform(float x, float y, float sizeX, float sizeY, std::string name);

	static std::map<std::string, Texture*> platform_sprites;

private:
	//Sprite* spr = nullptr;
	GameObject* platform = nullptr;
};