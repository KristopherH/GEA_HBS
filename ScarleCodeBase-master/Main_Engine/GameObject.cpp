#include "GameObject.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Collision_Manager.h"
#include "DXTKRenderer.h"
#include "Texture.h"


GameObject::GameObject(Sprite* _sprite, std::string _name, std::string _tag)
	:sprite(_sprite), name(_name), tag(_tag)
{

}

GameObject::GameObject()
{
	sprite = nullptr;
}

GameObject::GameObject(Sprite* _sprite)
	:sprite(_sprite)
{
}

GameObject::GameObject(std::vector<Sprite*> _sprite)
	: vectorSprites(_sprite)
{
}

GameObject::~GameObject()
{
	if (sprite != nullptr)
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

		box.minCorner.x = position.x;
		box.minCorner.y = position.y;
		box.maxCorner.x = position.x + this->getSize().x;
		box.maxCorner.y = position.y + this->getSize().y;


		sprite->setPosition(position);
		sprite->setRotation(rotation);
		sprite->setScale(scale);
	}

	if (physics)
	{
		velocity += acceleration * dt * speed;
		// apply Drag;
		acceleration.y *= 0.0f;
		acceleration.x *= 0.0f;
		velocity *= 0.99f;
		position += velocity;
	}
	return false;
}

bool GameObject::Draw()
{
	if (sprite)
	{
		return GameData::renderer->Draw(sprite);
	}
	return false;
}

void GameObject::setPosition(Vec2 * _position)
{
	position.x = _position->x; position.y = _position->y;
}

void GameObject::setSize(Vec2 * _size)
{
	size.x = _size->x;
	size.y = _size->y;
	if (sprite)
	{
		Vec2 textureSize = sprite->getSize();
		scale.x = _size->x / textureSize.x;
		scale.y = _size->y / textureSize.y;
	}
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

bool GameObject::isTransparent(Vec2 _pixel_pos, Rect box)
{
	return this->getSprite()->GetTexture()->isTransparent(_pixel_pos, box);
}

bool GameObject::isTransparent(Vec2 boxPos)
{
	return this->getSprite()->GetTexture()->isTransparent(boxPos);
}

void GameObject::movePosition(Vec2* _translation)
{
	position.x += _translation->x;
	position.y += _translation->y;
}

void GameObject::gravityUpdate()
{
	bool new_grounded = false;
	for (auto other : *GameData::go_list)
	{
		if (this != other && other->getSolid())
		{
			if (GameData::collsion_manager->boxCollision(
				this->box, other->getBox()))
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
	if (sprite)
	{
		return Vec2(sprite->getSize().x * scale.x, sprite->getSize().y * scale.y);
	}
	else
	{
		return size;
	}
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