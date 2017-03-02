#include "Enemy.h"
#include "GameDataV2.h"
#include "DXTKRenderer.h"


Enemy::Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
{
	SetSprite(new Sprite("enemy_sprite", GameDataV2::renderer));
	SetPosition(_pos);
	SetSize(_size);
	SetRotation(_rotation);
	setName(_name);
	setSolid(false);
}

Enemy::Enemy(Sprite * _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
	:GameObjectV2(_sprite)
{
	SetPosition(_pos);
	SetSize(_size);
	SetRotation(_rotation);
	setName(_name);
}

Enemy::~Enemy()
{
}
