#pragma once
//C++

//DXTK

//OURS
#include "..\DXTK_Wrapper\CustomMath.h"
#include "..\DXTK_Wrapper\DXTKRenderer.h"

class Texture;
class Renderer;

//=================================================================
// Sprite is a Texture with position scale and rotation,
//it is also the basic drawable object
//=================================================================

class Sprite
{
public:
	Sprite(Texture*);
	Sprite(std::string _fileName, Renderer* _renderer);
	virtual ~Sprite();

	virtual void Update();

	Texture* GetTexture() { return texture; }
	Vec4 getColour() { return colour; }
	Vec2 getOrigin() { return origin; }
	Vec2 getSize();
	Vec2 getScale();
	float getRotation();
	Vec2 getPosition();

	void setScale(Vec2);
	void setRotation(float);
	void setPosition(Vec2);
	void setOrigin(Vec2);

protected:

	Vec2 position;
	float rotation;
	Vec2 scale;
	Vec4 colour;
	Vec2 origin;
	Texture* texture;
};