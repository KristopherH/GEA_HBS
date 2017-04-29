#include "Collectible.h"
//C++
#include <vector>
#include <algorithm> // remove and remove_if

//DXTK

//OURS
#include "GameData.h"
#include "DXTKRenderer.h"
#include "Collision_Manager.h"
#include "SoundManager.h"
#include "Texture.h"
#include "Player.h"

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

bool Collectible::Update(float dt)
{
	GameObject::Update(dt);
	if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
	{
		alive = false;
		GameData::player->setScore();
		GameData::sound_manager->playSound("Collectible-SoundEffect.wav");
	}
	return false;
}
