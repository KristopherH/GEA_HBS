#include "GameObjectV2.h"
#include "GameDataV2.h"
#include "Collision_Manager.h"


GameObjectV2::GameObjectV2(Sprite* _sprite, std::string _name, std::string _tag)
	:sprite(_sprite), name(_name), tag(_tag)
{
}

GameObjectV2::GameObjectV2()
{
	sprite = nullptr;
}

GameObjectV2::GameObjectV2(Sprite* _sprite)
	:sprite(_sprite)
{
}

GameObjectV2::~GameObjectV2()
{
	if (sprite == nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void GameObjectV2::setSolid(bool _solid)
{
	solid = _solid;
}

bool GameObjectV2::getSolid()
{
	return solid;
}

bool GameObjectV2::Update()
{
	if (this->GetSprite())
	{
		box = Rect(Vec2(this->GetPosition().x, this->GetPosition().y),
			Vec2(this->GetPosition().x + this->GetSize().x,
				this->GetPosition().y + this->GetSize().y));
	}
	return false;
}

void GameObjectV2::SetSize(Vec2 * _size)
{
	Vec2 textureSize = sprite->GetSize();
	scale.x = _size->x / textureSize.x;
	scale.y = _size->y / textureSize.y;
	return;
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
	//Very messy Needs tidying up after alpha submission
	bool new_grounded = false;
	for (const auto& current_object : GameDataV2::go_list)
	{
		//This could be changed to solid now that's implemented (Post Alpha Task)
		for (const auto& current_gravity_tag : this->gravity_trigger_tags)
		{
			if (!gravity_on || this == current_object)
			{
				break;
			}
			else if (current_object->tag == current_gravity_tag)
			{
				if (GameDataV2::collsion_manager->boxCollision(
					this->name, current_object->getName()))
				{
					new_grounded = true;
					falling_speed = 0;
					break;
				}
			}

			if (new_grounded || !gravity_on)
			{
				break;
			}
		}
		if (new_grounded)
		{
			break;
		}
	}

	grounded = new_grounded;

	if (!grounded && gravity_on)
	{
		movePosition(new Vec2(0, falling_speed));
		falling_speed += gravity_acceleration;
	}
}

#pragma region getters and setters
Rect GameObjectV2::getBox()
{
	return box;
}

Direction GameObjectV2::getMovementDirection()
{
	return move_direction;
}

Vec2 GameObjectV2::GetPosition()
{
	return position;
}

Vec2 GameObjectV2::GetSize()
{
	return Vec2(sprite->GetSize().x * scale.x, sprite->GetSize().y * scale.y);
}

Vec2 GameObjectV2::GetScale()
{
	return scale;
}

Sprite * GameObjectV2::GetSprite()
{
	return sprite;
}

Vec2 GameObjectV2::GetOrigin()
{
	return origin;
}

float GameObjectV2::GetRotation()
{
	return rotation;
}

std::string GameObjectV2::getName()
{
	return name;
}

std::string GameObjectV2::getTag()
{
	return tag;
}
#pragma endregion