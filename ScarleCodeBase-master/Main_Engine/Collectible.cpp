#include "Collectible.h"
#include "GameDataV2.h"
#include "DXTKRenderer.h"
#include "Collision_Manager.h"
#include <vector>
#include <algorithm> // remove and remove_if
#include "Game_Controller.h"

Collectible::Collectible(Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
{
	setSprite(new Sprite("coin", GameDataV2::renderer));
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	setSolid(false);
}

Collectible::Collectible(Sprite * _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
	:GameObjectV2(_sprite)
{
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
}

Collectible::~Collectible()
{
}

bool Collectible::Update()
{
	if (GameDataV2::collsion_manager->boxCollision(name, "Player"))
	{
		alive = false;
	}
	return false;
}
