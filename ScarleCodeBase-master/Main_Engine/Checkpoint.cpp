#include "Checkpoint.h"
#include "Sprite.h"
#include "Collision_Manager.h"
#include "SoundManager.h"
#include "GameData.h"
#include "Player.h"

Checkpoint::Checkpoint(Vec2 * _pos, Vec2 * _size, float _rotation, std::string _name)
{
	setSprite(new Sprite("sign-2", GameData::renderer));
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	setSolid(false);
	active = true;
}

Checkpoint::Checkpoint(Sprite * _sprite, Vec2 * _pos, Vec2 * _size, float _rotation, std::string _name)
	:GameObject(_sprite)
{
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	active = true;
}

bool Checkpoint::Update(float dt)
{
	GameObject::Update(dt);

	if (active == true)
	{
		if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
		{
			//newCheckpoint = true;
			GameData::player->setLastCheckpoint(new Vec2(getPosition()));
			GameData::sound_manager->playSound("Checkpoint-SoundEffect.wav");
			active = false;
		}
	}
	return false;
}
