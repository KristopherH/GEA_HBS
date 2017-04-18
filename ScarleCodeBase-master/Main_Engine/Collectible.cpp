#include "Collectible.h"
//C++
#include <vector>
#include <algorithm> // remove and remove_if

//DXTK

//OURS
#include "GameData.h"
#include "DXTKRenderer.h"
#include "Collision_Manager.h"
#include "Game_Controller.h"
#include "Texture.h"

Collectible::Collectible(Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
{
	setSprite(new Sprite(new Texture("coin", GameData::renderer)));
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	setSolid(false);
}

Collectible::Collectible(Sprite * _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
	:GameObject(_sprite)
{
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
}

Collectible::~Collectible()
{
}

bool Collectible::Update(float dt)
{
	if (GameData::collsion_manager->boxCollision(name, "Player"))
	{
		alive = false;
	}
	return false;
}
