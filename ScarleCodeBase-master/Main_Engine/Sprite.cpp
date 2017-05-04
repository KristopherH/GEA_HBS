#include "Sprite.h"
//C++

//DXTK

//OURS
#include "Texture.h"

Sprite::Sprite(Texture* _texture) 
	:texture(_texture)
{
	//origin += texture->getSize();//around which rotation and scaing is done
	//origin *= 0.5f;
	int w = GetTexture()->getSize().x / frames_wide;
	int h = GetTexture()->getSize().y / frames_tall;
	setSpriteFrameWidth(w);
	setSpriteFrameHeight(h);
}

Sprite::Sprite(std::string _fileName, Renderer * _renderer)
	:Sprite(new Texture(_fileName, _renderer))
{
	
}

Sprite::~Sprite()
{
	/*if (texture)
		delete texture;
	texture = nullptr;*/
}

void Sprite::Update(float _dt)
{
}

void Sprite::animation(float _dt)
{
	animation_tick += _dt;

	if (animation_tick >= animation_length)
	{
		current_frame++;
		if (current_frame >= frames_per_animation)
			current_frame = 0;
		
		animation_tick = 0.0f;
		//Set the draw box and collision box
		int real_frame = current_frame * (int)animation_state;
		int frame_w = real_frame % frames_wide;
		int frame_h = real_frame / frames_wide;

		int h = 0;
		int w = 0;

		if (frame_h <= 0)
			h = 0;
		else
			h = getSize().y / frame_h;
		
		if (frame_w <= 0)
			w = 0;
		else
			w = getSize().x / frame_w;

		draw_box.minCorner.x = w * frame_w;
		draw_box.minCorner.y = h * frame_h;
		draw_box.maxCorner.x = draw_box.minCorner.x + w;
		draw_box.maxCorner.y = draw_box.minCorner.y + h;
	}


}

Vec2 Sprite::getSize()
{
	return Vec2((float)sprite_frame_width, (float)sprite_frame_height);
}

Vec2 Sprite::getTextureSize()
{
	return texture->getSize();
}

Vec2 Sprite::getScale()
{
	return scale;
}

float Sprite::getRotation()
{
	return rotation;
}

Vec2 Sprite::getPosition()
{
	return position;
}

float Sprite::getAnimationTick()
{
	return animation_tick;
}

float Sprite::getAnimationLength()
{
	return animation_length;
}

int Sprite::getSpriteFrameWidth()
{
	return sprite_frame_width;
}

int Sprite::getSpriteFrameHeight()
{
	return sprite_frame_height;
}

int Sprite::getFramesWide()
{
	return frames_wide;
}

int Sprite::getFramesTall()
{
	return frames_tall;
}

int Sprite::getFramesPerAnimation()
{
	return frames_per_animation;
}

int Sprite::getCurrentFrame()
{
	return current_frame;
}

int Sprite::getRealFrame()
{
	return real_frame;
}

Rect Sprite::getDrawBox()
{
	return draw_box;
}

Rect Sprite::getColliderBox()
{
	return collider_box;
}

AnimationState Sprite::getAnimationState()
{
	return animation_state;
}

void Sprite::setTexture(Texture * _texture)
{
	texture = _texture;
}

void Sprite::setScale(Vec2 _scale)
{
	scale.x = _scale.x;
	scale.y = _scale.y;
}

void Sprite::setRotation(float _rot)
{
	rotation = _rot;
}

void Sprite::setPosition(Vec2 _position)
{
	position.x = _position.x;
	position.y = _position.y;
}

void Sprite::setOrigin(Vec2 _origin)
{
	origin.x = _origin.x;
	origin.y = _origin.y;
}

void Sprite::increaseAnimationTick(float _increase)
{
	animation_tick += _increase;
}

void Sprite::setAnimationTick(float _animation_tick)
{
	animation_tick = _animation_tick;
}

void Sprite::setAnimationLength(float _animation_length)
{
	animation_length = _animation_length;
}

void Sprite::setSpriteFrameWidth(int _sprite_frame_width)
{
	sprite_frame_width = _sprite_frame_width;
}

void Sprite::setSpriteFrameHeight(int _sprite_frame_height)
{
	sprite_frame_height = _sprite_frame_height;
}

void Sprite::setFramesWide(int _frames_wide)
{
	frames_wide = _frames_wide;
	setSpriteFrameWidth(GetTexture()->getSize().x / frames_wide);
}

void Sprite::setFramesTall(int _frames_tall)
{
	frames_tall = _frames_tall;
	setSpriteFrameHeight(GetTexture()->getSize().y / frames_tall);
}

void Sprite::setFramesPerAnimation(int _frames_per_animation)
{
	frames_per_animation = _frames_per_animation;
}

void Sprite::setCurrentFrame(int _frame)
{
	current_frame = _frame;
}

void Sprite::setRealFrame(int _frame)
{
	real_frame = _frame;
}

void Sprite::setDrawBox(Rect _draw_box)
{
	draw_box = _draw_box;
}

void Sprite::setColliderBox(Rect _collider_box)
{
	collider_box = _collider_box;
}

void Sprite::setAnimationState(AnimationState _animation_state)
{
	animation_state = _animation_state;
}
