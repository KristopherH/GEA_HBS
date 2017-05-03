#include "MovingPlatform.h"
#include <algorithm>
#include "PlatformWaypoint.h"
#include "Player.h"
#include "Collision_Manager.h"
#include "Button.h"
#include "Object_Factory.h"
#include "Helper.h"

MovingPlatform::~MovingPlatform()
{
}

MovingPlatform * MovingPlatform::create(PLATFORM_TYPE type)
{
	MovingPlatform* platform = new MovingPlatform(new Sprite(platform_sprites["Standard"]), "Platform", "StandardPlatform");
	platform->waypoints.push_back(Vec2(0.0f, 0.0f));
	platform->changeType(type);
	return platform;
}

MovingPlatform * MovingPlatform::create(PLATFORM_TYPE type, std::vector<Vec2> _waypoints)
{
	MovingPlatform* platform = MovingPlatform::create(type);
	platform->setWaypoints(_waypoints);
	return platform;
}

bool MovingPlatform::Update(float dt)
{
	if (waypoints.size() > 0)
	{
		acceleration.x = 0; acceleration.y = 0;
		Vec2 movement(waypoints[current_waypoint] - position);
		movement.Limit(max_speed);
		velocity.x = movement.x;
		velocity.y = movement.y;
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
	if (GameData::collsion_manager->boxCollision(this->box, GameData::player->getBox()))
	{
		GameData::player->movePosition(&velocity);
	}
	return Platform::Update(dt);
}

void MovingPlatform::setWaypoints(std::vector<Vec2> _waypoints)
{
	waypoints.clear();
	for (int i = 0; i < _waypoints.size(); i++)
	{
		waypoints.push_back(_waypoints[i]);
	}
	current_waypoint = 0;
}

MovingPlatform::MovingPlatform(Sprite* sprite, std::string _name, std::string _tag)
	:Platform(sprite, _name, _tag)
{

}

void MovingPlatform::toggleEditing()
{
	Platform::toggleEditing();
	if (editing)
	{
		//create waypoints and add them to the main GO-list
		for (int i = 0; i < waypoints.size(); i++)
		{
			PlatformWaypoint* wp = new PlatformWaypoint(this, i);
			//GameData::go_list->push_back(wp);
			ui_elements.push_back(wp);
			wp->setSize(&size);
			wp->setPosition(&waypoints[i]);
		}

		Button* waypointsNumber = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", "Waypoints:" + Helper::to_string_with_precision(waypoints.size()));
		waypointsNumber->setSize(new Vec2(max(size.x, 100), 50));
		waypointsNumber->setPosition(new Vec2(position.x, position.y + size.y + waypointsNumber->getSize().y));
		waypointsNumber->setCallbackFunction([this, waypointsNumber]()
		{
			return;
		});
		waypointsNumber->setScreenSpace(false);
		ui_elements.push_back(waypointsNumber);

		Button* plusType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		plusType->setSize(new Vec2(50, 50));
		plusType->setPosition(new Vec2(position.x + waypointsNumber->getSize().x, position.y + size.y + waypointsNumber->getSize().y));
		plusType->setCallbackFunction([this, waypointsNumber]()
		{
			addWaypoint();
			waypointsNumber->setText("Waypoints:" + Helper::to_string_with_precision(waypoints.size()));
			return;
		});
		plusType->setScreenSpace(false);
		ui_elements.push_back(plusType);

		Button* minusType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minusType->setSize(new Vec2(50, 50));
		minusType->setPosition(new Vec2(position.x - minusType->getSize().x, position.y + size.y + waypointsNumber->getSize().y));
		minusType->setCallbackFunction([this, waypointsNumber]()
		{
			removeWaypoint();
			waypointsNumber->setText("Waypoints:" + Helper::to_string_with_precision(waypoints.size()));
			return;
		});
		minusType->setScreenSpace(false);
		ui_elements.push_back(minusType);



		Button* speedBtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", "Speed:" + Helper::to_string_with_precision(max_speed));
		speedBtn->setSize(new Vec2(max(size.x, 100), 50));
		speedBtn->setPosition(new Vec2(position.x,
			position.y + size.y + waypointsNumber->getSize().y + waypointsNumber->getSize().y));
		speedBtn->setCallbackFunction([this, speedBtn]()
		{
			return;
		});
		speedBtn->setScreenSpace(false);
		ui_elements.push_back(speedBtn);

		Button* plusSpeed = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		plusSpeed->setSize(new Vec2(50, 50));
		plusSpeed->setPosition(new Vec2(position.x + speedBtn->getSize().x,
			position.y + size.y + waypointsNumber->getSize().y + waypointsNumber->getSize().y));
		plusSpeed->setCallbackFunction([this, speedBtn]()
		{
			max_speed += 0.2f;
			speedBtn->setText("Speed:" + Helper::to_string_with_precision(max_speed));
			return;
		});
		plusSpeed->setScreenSpace(false);
		ui_elements.push_back(plusSpeed);

		Button* minusSpeed = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minusSpeed->setSize(new Vec2(50, 50));
		minusSpeed->setPosition(new Vec2(position.x - minusSpeed->getSize().x,
			position.y + size.y + waypointsNumber->getSize().y + waypointsNumber->getSize().y));
		minusSpeed->setCallbackFunction([this, speedBtn]()
		{
			max_speed -= 0.2f;
			speedBtn->setText("Speed:" + Helper::to_string_with_precision(max_speed));
			return;
		});
		minusSpeed->setScreenSpace(false);
		ui_elements.push_back(minusSpeed);

	}
}

void MovingPlatform::addWaypoint()
{
	Vec2 pos = Vec2(position.x + size.x, position.y);
	waypoints.push_back(pos);
	reToggleEditing = true;
}

void MovingPlatform::removeWaypoint()
{
	if (waypoints.size() > 1)
	{
		waypoints.pop_back();
		reToggleEditing = true;
	}
}
