#include "GameObjectV2.h"
#include "GameDataV2.h"
#include "Collision_Manager.h"

GameObjectV2::GameObjectV2(Sprite* _sprite, std::string _name, std::string _tag)
	:sprite(_sprite), name(_name), tag(_tag)
{
}

GameObjectV2::~GameObjectV2()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

bool GameObjectV2::Update()
{
	return false;
}

bool GameObjectV2::setGravityTag(std::string _gravity_tag)
{
	for (const auto& gravity_tag : this->gravity_trigger_tags)
	{
		if (gravity_tag == _gravity_tag)
		{
			return false;
		}
	}

	this->gravity_trigger_tags.push_back(_gravity_tag);
	return true;
}

void GameObjectV2::movePosition(Vec2* _translation)
{
	position.x += _translation->x;
	position.y += _translation->y;
}

void GameObjectV2::gravityUpdate()
{
	int i = 0;

	for (const auto& current_object : GameDataV2::go_list)
	{
		i++;
		for (const auto& current_gravity_tag : this->gravity_trigger_tags)
		{
			if (!gravity_on)
			{
				break;
			}
			else if (current_object->tag == current_gravity_tag)
			{
				if (GameDataV2::collsion_manager->boxCollision(
					this->name, current_object->getName()))
				{
					grounded = true;
					falling_speed = 0;
					break;
				}
				else
				{
					grounded = false;
				}
			}

			if (grounded || !gravity_on)
			{
				break;
			}
		}

	}

	if (!grounded && gravity_on)
	{
		movePosition(new Vec2(0, falling_speed));
		falling_speed += gravity_acceleration;
	}

	i = 0;
}