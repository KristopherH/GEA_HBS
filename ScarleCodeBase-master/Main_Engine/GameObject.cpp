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
		sprite->Update(dt); 
		if(animated)
			animation(dt);
		if(tag == "Button")
		{
			box.minCorner.x = getPosition().x;
			box.minCorner.y = getPosition().y;
			box.maxCorner.x = getPosition().x + getSize().x;
			box.maxCorner.y = getPosition().y + getSize().y;
		}
		else
			box = sprite->getColliderBox();

		Rect col_box;
		col_box.minCorner.x = position.x;
		col_box.minCorner.y = position.y;
		col_box.maxCorner.x = position.x + getSize().x;
		col_box.maxCorner.y = position.y + getSize().y;

		sprite->setColliderBox(col_box);
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
		if (this->getTag() == "Player")
			return GameData::renderer->Draw(this);

		return GameData::renderer->Draw(sprite);
	}
	return false;
}

void GameObject::setPosition(Vec2 * _position)
{
	position.x = _position->x; position.y = _position->y;
	if (sprite != nullptr)
	{
		bottomCollider = Rect(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
		bottomCollider.maxCorner += sprite->getSize();
		bottomCollider.minCorner += Vec2(0.0f, sprite->getSize().y);
		bottomCollider.maxCorner *= scale;
		bottomCollider.minCorner *= scale;
	}
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
						this->sprite->getColliderBox(), current_object->getBox()))
					{
						Rect top_of_the_platform(current_object->getBox()/* + current_object->getPosition()*/);
						top_of_the_platform.maxCorner.y = top_of_the_platform.minCorner.y + 60.0f;
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

void GameObject::animation(float _dt)
{
	sprite->increaseAnimationTick(_dt);
	float ani_tick = sprite->getAnimationTick();
	float ani_length = sprite->getAnimationLength();
	int cur_frame = sprite->getCurrentFrame();
	int frames_per_ani = sprite->getFramesPerAnimation();
	int frames_col = sprite->getFramesWide();
	AnimationState ani = sprite->getAnimationState();

	if (ani_tick >= ani_length)
	{
		cur_frame++;
		if (cur_frame >= frames_per_ani)
			cur_frame = 1;

		sprite->setCurrentFrame(cur_frame);
		sprite->setAnimationTick(0.0f);
		//Set the draw box and collision box
		int real_frame = cur_frame * (int)ani;
		int frame_w = real_frame % frames_col;
		int frame_h = real_frame / frames_col;

		int max_y = 0;
		int max_x = 0;
		int min_x = 0;
		int min_y = 0;

		if (frame_h <= 0)
			min_y = 0;
		else
			min_y = sprite->getSpriteFrameHeight() * frame_h;

		if (frame_w <= 0)
			min_x = 0;
		else
			min_x = sprite->getSpriteFrameWidth() * frame_w;

		Rect source;
		source.minCorner.x = min_x;
		source.minCorner.y = min_y;
		source.maxCorner.x = min_x + sprite->getSpriteFrameWidth();
		source.maxCorner.y = min_y + sprite->getSpriteFrameHeight();

		sprite->setDrawBox(source);
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