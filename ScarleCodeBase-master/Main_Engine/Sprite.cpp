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
}

Sprite::Sprite(std::string _fileName, Renderer * _renderer)
	:Sprite(new Texture(_fileName, _renderer))
{
	
}

Sprite::~Sprite()
{
	if (texture)
		delete texture;
	texture = nullptr;
}

void Sprite::Update()
{
}

Vec2 Sprite::getSize()
{
	return texture->getSize();
}

Vec2 Sprite::getScale()
{
	return scale; //HERE
}

float Sprite::getRotation()
{
	return rotation;
}

Vec2 Sprite::getPosition()
{
	return position;
}

Rect Sprite::getSource()
{
	return source;
}

Rect Sprite::getDestination()
{
	return destination;
}

int Sprite::getSpritesAcross()
{
	return sprites_across;
}

int Sprite::getSpritesDown()
{
	return sprites_down;
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

void Sprite::setSource(Rect _source)
{
	source = _source;
}

void Sprite::setDestination(Rect _destination)
{
	destination = _destination;
}

void Sprite::setSpritesAcross(int _sprites_across)
{
	sprites_across = _sprites_across;
}

void Sprite::setSpritesDown(int _sprites_down)
{
	sprites_down = _sprites_down;
}

void Sprite::setFrameWidth(int _frame_width)
{
	frame_width = _frame_width;
	scale.x *= frame_width;
}

int Sprite::getFrameWidth()
{
	return frame_width;
}

void Sprite::setFrameHeight(int _frame_height)
{
	frame_height = _frame_height;
	scale.y *= frame_height;
}

int Sprite::getFrameHeight()
{
	return frame_height;
}