#include "Enemy.h"
//C++
#include <vector>
#include <algorithm> // remove and remove_if

//DXTK

//OURS
#include "GameData.h"
#include "DXTKRenderer.h"
#include "Collision_Manager.h"
#include "Game_Controller.h"
#include "Player.h"
#include "EnemyWaypoint.h"

Enemy::Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
{
	setSprite(new Sprite("enemy_sprite", GameData::renderer));
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	setSolid(false);
	if (waypoints.size() == 0)
	{
		waypoints.push_back(position);
	}
}

Enemy::Enemy(Sprite * _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
	:GameObject(_sprite)
{
	setPosition(_pos);
	setSize(_size);
	setRotation(_rotation);
	setName(_name);
	setSolid(false);
	if (waypoints.size() == 0)
	{
		waypoints.push_back(position);
	}
}

Enemy::Enemy(Sprite * _sprite, Vec2 * _pos, Vec2 * _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints)
	:Enemy(_sprite, _pos, _size, _rotation, _name)
{
	waypoints.clear();
	for (int i = 0; i < _waypoints.size(); i++)
	{
		waypoints.push_back(_waypoints[i]);
	}
	current_waypoint = 0;
}

Enemy::Enemy(Vec2 * _pos, Vec2 * _size, float _rotation, std::string _name, std::vector<Vec2> _waypoints)
	:Enemy(_pos, _size, _rotation, _name)
{
	waypoints.clear();
	for (int i = 0; i < _waypoints.size(); i++)
	{
		waypoints.push_back(_waypoints[i]);
	}
	current_waypoint = 0;
}

Enemy::~Enemy()
{
}

bool Enemy::Update(float dt)
{
	if (GameData::collsion_manager->boxCollision(name, "Player"))
	{
 		GameData::player->killPlayer();
		alive = false;
	}
	if (waypoints.size() > 0)
	{
		acceleration.x = 0; acceleration.y = 0;
		Vec2 movement((((waypoints[current_waypoint]) - position)));
		movement.Normalize();
		acceleration +=  movement * 0.1f;
		acceleration.Limit(max_speed);
		if (Vec2::DistanceSqrd(position, (waypoints[current_waypoint])) < 10.0f)
		{
			velocity.x = 0; velocity.y = 0;
			current_waypoint++;
			if (current_waypoint == waypoints.size())
			{
				current_waypoint = 0;
			}
		}
	}

	GameObject::Update(dt);
	return false;
}

bool Enemy::Draw()
{
	return GameObject::Draw();
}

void Enemy::toggleWaypoints()
{
	displayWaypoints = !displayWaypoints;
	if (!displayWaypoints)
	{
		GameData::go_list->erase(std::remove_if(GameData::go_list->begin(),
			GameData::go_list->end(),
			[this](GameObject* go)
		{
			// find waypoint in GO_LIST and delete them
			for (auto& wp : waypointsGOs)
			{
				if (wp == go)
				{
					return true;
				}
			}
			return false;
		}), GameData::go_list->end());
		for (auto& wp : waypointsGOs)
		{
			delete wp;
		}
		waypointsGOs.clear();
	}
	else if (displayWaypoints)
	{
		//create waypoints and add them to the main GO-list
		for (int i = 0; i < waypoints.size(); i++)
		{
			EnemyWaypoint* wp = new EnemyWaypoint(this, i);
			GameData::go_list->push_back(wp);
			waypointsGOs.push_back(wp);
			wp->setSize(&size);
			wp->setPosition(&waypoints[i]);
		}
	}
}

void Enemy::addWaypoint()
{
	Vec2 pos = position + size;
	waypoints.push_back(pos);
	toggleWaypoints();
	toggleWaypoints();
}

void Enemy::removeWaypoint()
{
	if (waypoints.size() > 1)
	{
		waypoints.pop_back();
		toggleWaypoints();
		toggleWaypoints();
	}
}

