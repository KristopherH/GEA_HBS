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
	if (this->getSprite())
	{
		box = Rect(Vec2(this->getPosition().x, this->getPosition().y),
			Vec2(this->getPosition().x + this->getSize().x,
				this->getPosition().y + this->getSize().y));
	}

	velocity += acceleration;
	// apply Drag;
	acceleration.y *= 0.99f;
	acceleration.x *= 0.95f;
	velocity *= 0.9f;
	position += velocity;

	return false;
}

void GameObjectV2::setSize(Vec2 * _size)
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
	/*if (!gravity_on)
	{
		return;
	}*/
	//Very messy Needs tidying up after alpha submission
	bool new_grounded = false;
	for (const auto& current_object : GameDataV2::go_list)
	{
		//This could be changed to solid now that's implemented (Post Alpha Task)
		for (const auto& current_gravity_tag : this->gravity_trigger_tags)
		{
			if (this != current_object)
			{
				if (current_object->tag == current_gravity_tag)
				{
					if (GameDataV2::collsion_manager->boxCollision(
						this->name, current_object->getName()))
					{
						if (!grounded)
						{
							velocity.y = 0.0f;
							acceleration.y = 0.0f;
						}
						//if (GameDataV2::collsion_manager->getCollisionDirection() == Direction::TOP)
						{
							new_grounded = true;
						}
						break;
					}
				}
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
		acceleration.y += gravity_constant;
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

Vec2 GameObjectV2::getPosition()
{
	return position;
}

Vec2 GameObjectV2::getSize()
{
	return Vec2(sprite->GetSize().x * scale.x, sprite->GetSize().y * scale.y);
}

Vec2 GameObjectV2::getScale()
{
	return scale;
}

Sprite * GameObjectV2::getSprite()
{
	return sprite;
}

Vec2 GameObjectV2::getOrigin()
{
	return origin;
}

float GameObjectV2::getRotation()
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