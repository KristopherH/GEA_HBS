#include "Sprite.h"
//C++

//DXTK
#if defined _DXTK_
#include "..\DXTK_Wrapper\Renderer.h"
#include "../DXTK_Wrapper/Texture.h"
#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/Texture.h"
#include "../Phyre/Code/Renderer.h"
#endif

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