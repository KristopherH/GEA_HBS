#include "Checkpoint.h"
#include "Sprite.h"
#include "Collision_Manager.h"
#include "SoundManager.h"
#include "GameData.h"
#include "Player.h"

Checkpoint::Checkpoint(Sprite * _sprite, Vec2 _pos, Vec2 _size, float _rotation, std::string _name)
	:EditableGameObject(_sprite)
{
	setSize(&_size);
	setPosition(&_pos);
	setRotation(_rotation);
	setName(_name);
	setType("Checkpoint");
	setSolid(false);
	active = true;
}

bool Checkpoint::Update(float dt)
{
	EditableGameObject::Update(dt);
	if (active == true)
	{
		if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
		{
			GameData::player->setLastCheckpoint(new Vec2(getPosition()));
			
			GameData::sound_manager->playSound("Checkpoint-SoundEffect.wav");
			active = false;
		}
	}
	return false;
}
