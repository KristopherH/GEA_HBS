#pragma once
//C++
#include <vector>
#include <chrono>

//DXTK

//OURS
#include "..\DXTK_Wrapper\CustomMath.h"
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "Sprite.h"

class Texture;
class Renderer;

//=================================================================
// Sprite is a Texture with position scale and rotation,
//it is also the basic drawable object
//=================================================================

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(std::vector<Texture*>);
	//AnimatedSprite(Texture*, Vec2 size, int count);
	virtual ~AnimatedSprite();

	//void Update() override;

	void nextAnimation();

	std::vector<Texture*> GetTextureArray() { return textureArray; }

protected:
	std::vector<Texture*> textureArray;
	std::vector<Texture*>::iterator currentTexture;

	float animationTimer = 1.0f;
	std::chrono::time_point<std::chrono::system_clock> start;
};