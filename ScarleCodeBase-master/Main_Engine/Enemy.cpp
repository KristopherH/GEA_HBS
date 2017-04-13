#include "Enemy.h"
//C++
#include <vector>
#include <algorithm> // remove and remove_if

//DXTK

//OURS
#include "GameDataV2.h"
#include "DXTKRenderer.h"
#include "Collision_Manager.h"
#include "Game_Controller.h"

Enemy::Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
{
	setSprite(new Sprite("enemy_sprite", GameDataV2::renderer));
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	setSolid(false);
}

Enemy::Enemy(Sprite * _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
	:GameObjectV2(_sprite)
{
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	setSolid(false);
}

Enemy::Enemy(Sprite * _sprite, Vec2 * _pos, Vec2 * _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints)
	:Enemy(_sprite, _pos, _size, _rotation, _name)
{
	waypoints = _waypoints;
	current_waypoint = waypoints.begin();
}

Enemy::Enemy(Vec2 * _pos, Vec2 * _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints)
	:Enemy(_pos, _size, _rotation, _name)
{
	waypoints = _waypoints;
	current_waypoint = waypoints.begin();
}

Enemy::~Enemy()
{
}

bool Enemy::Update()
{
	if (GameDataV2::collsion_manager->boxCollision(name, "Player"))
	{
 		player = new PlayerV2();
 		player->setLives();
		alive = false;
	}
	if (waypoints.size() > 1)
	{
		acceleration.x = 0; acceleration.y = 0;
		Vec2 movement((((*current_waypoint) - position)));
		movement.Normalize();
		acceleration +=  movement /* * dt*/ * 0.1f;
		acceleration.Limit(max_speed);
		if (Vec2::DistanceSqrd(position, (*current_waypoint)) < 10.0f)
		{
			velocity.x = 0; velocity.y = 0;
			current_waypoint++;
			if (current_waypoint == waypoints.end())
			{
				current_waypoint = waypoints.begin();
			}
		}
	}
	GameObjectV2::Update();
	return false;
}

