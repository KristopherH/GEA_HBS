#pragma once
#include "GameObject.h"
#include "MovingPlatform.h"

class PlatformWaypoint : public GameObject
{
public:
	PlatformWaypoint(MovingPlatform* _parent, int _index);
	~PlatformWaypoint();

	void setPosition(Vec2* _position) override;
	void movePosition(Vec2* _translation) override;

	MovingPlatform* parent;
	int index;
};