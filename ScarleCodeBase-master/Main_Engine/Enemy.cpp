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
#include "Button.h"
#include "Object_Factory.h"

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
	:EditableGameObject(_sprite)
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
	if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
	{
 		GameData::player->killPlayer();
		//alive = false; //Enemies don't die in the original game;
	}
	if (waypoints.size() > 0)
	{
		acceleration.x = 0; acceleration.y = 0;
		if (current_waypoint > waypoints.size())
		{
			current_waypoint = 0;
		}
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
	EditableGameObject::Update(dt);
	return false;
}

bool Enemy::Draw()
{
	return EditableGameObject::Draw();
}

void Enemy::toggleEditing()
{
	EditableGameObject::toggleEditing();
	if (editing)
	{
		//create waypoints and add them to the main GO-list
		for (int i = 0; i < waypoints.size(); i++)
		{
			EnemyWaypoint* wp = new EnemyWaypoint(this, i);
			//GameData::go_list->push_back(wp);
			ui_elements.push_back(wp);
			wp->setSize(&size);
			wp->setPosition(&waypoints[i]);
		}

		Button* waypointsNumber = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]), 
			"NameChanger", "NULL", "Waypoints:" + to_string(waypoints.size()));
		waypointsNumber->setSize(new Vec2(max(size.x, 100), 50));
		waypointsNumber->setPosition(new Vec2(position.x, position.y + size.y));
		waypointsNumber->setCallbackFunction([this, waypointsNumber]()
		{
			return;
		});
		waypointsNumber->setScreenSpace(false);
		ui_elements.push_back(waypointsNumber);

		Button* plusType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		plusType->setSize(new Vec2(50, 50));
		plusType->setPosition(new Vec2(position.x + waypointsNumber->getSize().x, position.y + size.y));
		plusType->setCallbackFunction([this, waypointsNumber]()
		{
			addWaypoint();
			waypointsNumber->setText("Waypoints:" + to_string(waypoints.size()));
			return;
		});
		plusType->setScreenSpace(false);
		ui_elements.push_back(plusType);

		Button* minusType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minusType->setSize(new Vec2(50, 50));
		minusType->setPosition(new Vec2(position.x - minusType->getSize().x, position.y + size.y));
		minusType->setCallbackFunction([this, waypointsNumber]()
		{
			removeWaypoint();
			waypointsNumber->setText("Waypoints:" + to_string(waypoints.size()));
			return;
		});
		minusType->setScreenSpace(false);
		ui_elements.push_back(minusType);



		Button* speedBtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", "Speed:" + to_string(max_speed));
		speedBtn->setSize(new Vec2(max(size.x, 100), 50));
		speedBtn->setPosition(new Vec2(position.x, 
						position.y + size.y + waypointsNumber->getSize().y));
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
							position.y + size.y + waypointsNumber->getSize().y));
		plusSpeed->setCallbackFunction([this, speedBtn]()
		{
			max_speed += 0.2f;
			speedBtn->setText("Speed:" + to_string(max_speed));
			return;
		});
		plusSpeed->setScreenSpace(false);
		ui_elements.push_back(plusSpeed);

		Button* minusSpeed = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minusSpeed->setSize(new Vec2(50, 50));
		minusSpeed->setPosition(new Vec2(position.x - minusSpeed->getSize().x,
							position.y + size.y + waypointsNumber->getSize().y));
		minusSpeed->setCallbackFunction([this, speedBtn]()
		{
			max_speed -= 0.2f;
			speedBtn->setText("Speed:" + to_string(max_speed));
			return;
		});
		minusSpeed->setScreenSpace(false);
		ui_elements.push_back(minusSpeed);
		
	}
}

void Enemy::addWaypoint()
{
	Vec2 pos = Vec2(position.x + size.x, position.y);
	waypoints.push_back(pos);
	reToggleEditing = true;
}

void Enemy::removeWaypoint()
{
	if (waypoints.size() > 1)
	{
		waypoints.pop_back();
	}
	reToggleEditing = true;
}

