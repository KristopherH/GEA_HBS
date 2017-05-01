#include "GameObject.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Collision_Manager.h"
#include "DXTKRenderer.h"
#include "Texture.h"


//GameObject::GameObject(Sprite* _sprite, std::string _name, std::string _tag)
//	:sprite(_sprite), name(_name), tag(_tag)
//{
//
//}

GameObject::GameObject()
{
	sprite = nullptr;
}

GameObject::GameObject(Sprite * _sprite, std::string _name, std::string _tag, int _sprites_across, int _sprites_down) :
	sprite(_sprite), name(_name), tag(_tag)
{
	if (tag == "Player")
		int i = 0;

	sprite->setSpritesAcross(_sprites_across);
	sprite->setSpritesDown(_sprites_down);

	int width = this->getSize().x / _sprites_across;
	int height = this->getSize().y / _sprites_down;

	sprite->setFrameWidth(width);
	sprite->setFrameHeight(height);
}

GameObject::GameObject(Sprite* _sprite)
	:sprite(_sprite)
{
}

GameObject::~GameObject()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void GameObject::setSolid(bool _solid)
{
	solid = _solid;
}

bool GameObject::getSolid()
{
	return solid;
}

bool GameObject::Update(float dt)
{
	if (this->getSprite())
	{
		sprite->Update();
		int width = this->size.x / this->getSprite()->getSpritesAcross();
		int height = this->size.y / this->getSprite()->getSpritesDown();

 		box.min.x = position.x;
		box.min.y = position.y;
 		box.max.x = position.x + width;
		box.max.y = position.y + height;

		sprite->setPosition(position);
		sprite->setRotation(rotation);
		sprite->setScale(scale);

		animation(dt);
	}

	velocity += acceleration;
	// apply Drag;
	acceleration.y *= 0.99f;
	acceleration.x *= 0.95f;
	velocity *= 0.9f;
	position += velocity * dt * speed;

	return false;
}

bool GameObject::Draw()
{
	return GameData::renderer->Draw(sprite, frame_tick);
}

void GameObject::setPosition(Vec2 * _position)
{
	position.x = _position->x; position.y = _position->y;
	if (sprite != nullptr)
	{
		bottomCollider = Rect(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
		bottomCollider.max += sprite->getSize();
		bottomCollider.min += Vec2(0.0f, sprite->getSize().y);
		bottomCollider.max *= scale;
		bottomCollider.min *= scale;
	}
}

void GameObject::setSize(Vec2 * _size)
{
	size.x = _size->x;
	size.y = _size->y;
	Vec2 textureSize = sprite->getSize();
	scale.x = _size->x / textureSize.x;
	scale.y = _size->y / textureSize.y;
	return;
}

bool GameObject::setGravityTag(std::string _gravity_tag)
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

void GameObject::animation(float _dt)
{
	animation_tick += _dt;
	if (animation_tick >= animation_delay)
	{
		animation_tick = 0.0f;
		frame_tick++;
		if (frame_tick >= this->getSprite()->getSpritesAcross())
			frame_tick = 0;
		    //bump height 
	}
}

void GameObject::movePosition(Vec2* _translation)
{
	position.x += _translation->x;
	position.y += _translation->y;
}

void GameObject::gravityUpdate()
{
	/*if (!gravity_on)
	{
		return;
	}*/
	//Very messy Needs tidying up after alpha submission
	bool new_grounded = false;
	for (const auto& current_object : *GameData::go_list)
	{
		//This could be changed to solid now that's implemented (Post Alpha Task)
		for (const auto& current_gravity_tag : this->gravity_trigger_tags)
		{
			if (this != current_object)
			{
				if (current_object->tag == current_gravity_tag)
				{
					if (GameData::collsion_manager->boxCollision(
						this->box, current_object->getBox()))
					{
						Rect top_of_the_platform(current_object->getBox()/* + current_object->getPosition()*/);
						top_of_the_platform.max.y = top_of_the_platform.min.y + 60.0f;
						if (GameData::collsion_manager->boxCollision(
							bottomCollider + position , top_of_the_platform))
						{
							if (velocity.y >= 0.0f)
							{
								if (!grounded) // If not previously grounded
								{
									velocity.y = 0.0f;
									acceleration.y = 0.0f;
								}

								new_grounded = true;
								break;
							}
						}
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
Rect GameObject::getBox()
{
	return box;
}

Direction GameObject::getMovementDirection()
{
	return move_direction;
}

Vec2 GameObject::getPosition()
{
	return position;
}

Vec2 GameObject::getSize()
{
	return Vec2(size.x, size.y);
}

Vec2 GameObject::getScale()
{
	return scale;
}

Sprite * GameObject::getSprite()
{
	return sprite;
}

Vec2 GameObject::getOrigin()
{
	return origin;
}

float GameObject::getRotation()
{
	return rotation;
}

std::string GameObject::getName()
{
	return name;
}

std::string GameObject::getTag()
{
	return tag;
}
#pragma endregion