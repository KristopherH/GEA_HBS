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


	

private:
	//Sprite* spr = nullptr;
	GameObject* platform = nullptr;
};