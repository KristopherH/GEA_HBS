#include "PlatformWaypoint.h"

PlatformWaypoint::PlatformWaypoint(MovingPlatform * _parent, int _index)
	:GameObject(new Sprite("PlatformWaypoint", GameData::renderer), "Waypoint", "Waypoint"),
	parent(_parent), index(_index)
{
	setType("Waypoint");
}

PlatformWaypoint::~PlatformWaypoint()
{
}

void PlatformWaypoint::setPosition(Vec2 * _position)
{
	GameObject::setPosition(_position);
	parent->waypoints[index] = *_position;
}

void PlatformWaypoint::movePosition(Vec2 * _translation)
{
	GameObject::movePosition(_translation);
	parent->waypoints[index] += *_translation;
}
