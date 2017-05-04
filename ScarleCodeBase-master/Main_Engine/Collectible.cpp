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
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "Player.h"
#include "Object_Factory.h"

Collectible::Collectible(Sprite * _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
	:EditableGameObject(_sprite)
{
	setSize(_size);
	setPosition(_pos);
	setRotation(_rotation);
	setName(_name);
	setType("Collectible");
	setSolid(false);
}

Collectible::~Collectible()
{
}

bool Collectible::Update(float dt)
{
	EditableGameObject::Update(dt);
	if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
	{
		if (GameData::collsion_manager->bitMapCollision(*GameData::player, *this))
		{
			alive = false;
			GameData::player->setScore();
			GameData::sound_manager->playSound("Collectible-SoundEffect.wav");
		}
	}

	return false;
}
