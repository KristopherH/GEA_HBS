#pragma once
#include "Platform.h"

class MovingPlatform : public Platform
{
	friend class PlatformWaypoint;
	friend class LevelLoader;
public:
	~MovingPlatform();

	static MovingPlatform* create(PLATFORM_TYPE);
	static MovingPlatform* create(PLATFORM_TYPE, std::vector<Vec2> waypoints);

	bool Update(float dt) override;
	//bool Draw();

	void setWaypoints(std::vector<Vec2> waypoints);

	void toggleEditing();

	void addWaypoint();
	void removeWaypoint();
private:
	MovingPlatform(Sprite* sprite, std::string _name, std::string _tag);

	std::vector<Vec2> waypoints;
	int current_waypoint = 0;
};