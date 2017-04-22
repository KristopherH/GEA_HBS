#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::vector<Texture*> _textureArray)
	:Sprite(_textureArray[0])
{
	textureArray = _textureArray;
	currentTexture = textureArray.begin();
}

//AnimatedSprite::AnimatedSprite(Texture* _sprite, Vec2 size, int count)
//	:Sprite(_sprite)
//{
//
//}

AnimatedSprite::~AnimatedSprite()
{
	for (auto& text : textureArray)
	{
		delete text;
	}
	textureArray.clear();
}

void AnimatedSprite::Update()
{
	std::chrono::duration<float> elapsed_seconds = std::chrono::system_clock::now() - start;
	if (elapsed_seconds.count() > animationTimer)
	{
		nextAnimation();
		start = std::chrono::system_clock::now();
	}
}

void AnimatedSprite::nextAnimation()
{
	currentTexture++;
	if (currentTexture == textureArray.end())
	{
		currentTexture = textureArray.begin();
	}
	texture = *currentTexture;
}
