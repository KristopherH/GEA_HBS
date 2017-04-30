#include "EnemyWaypoint.h"
#include "Enemy.h"

EnemyWaypoint::EnemyWaypoint(Enemy* _parent, int _index)
	:GameObject(new Sprite("Waypoint", GameData::renderer), "Waypoint", "EnemyWaypoint"), 
	parent(_parent), index(_index)
{

}

EnemyWaypoint::~EnemyWaypoint()
{
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