#include "EnemyWaypoint.h"
#include "Enemy.h"
#include "Collision_Manager.h"
#include "Input_Manager.h"

EnemyWaypoint::EnemyWaypoint(Enemy* _parent, int _index)
	:GameObject(new Sprite("Waypoint", GameData::renderer), "Waypoint", "Waypoint"), 
	parent(_parent), index(_index)
{
	setType("Waypoint");
}

EnemyWaypoint::~EnemyWaypoint()
{
}

bool EnemyWaypoint::Update(float dt)
{
	GameObject::Update(dt);
	return false;
}

void EnemyWaypoint::setPosition(Vec2 * _position)
{
	GameObject::setPosition(_position);
	parent->waypoints[index] = *_position;
}

void EnemyWaypoint::movePosition(Vec2 * _translation)
{
	GameObject::movePosition(_translation);
	parent->waypoints[index] += *_translation;
}