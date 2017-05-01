#pragma once
//C++
#include <map>

//DXTK

//OURS
#include "..\DXTK_Wrapper\CustomMath.h"
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "../Main_Engine/GameData.h"
#include "../DXTK_Wrapper/Texture.h"

class Renderer;

enum AnimationStates
{
	IDLE,
	WALKING,
	RUNNING,
	JUMPING,
	ATTACKING,
	DYING
};

//=================================================================
// Sprite is a Texture with position scale and rotation,
//it is also the basic drawable object
//=================================================================

class Sprite
{
public:
	Sprite(Texture* _texture, AnimationStates _animation_state = AnimationStates::IDLE);
	Sprite(std::string _fileName, Renderer* _renderer = GameData::renderer);
	virtual ~Sprite();

	virtual void Update();

	Texture* GetTexture() { return texture; }
	Vec4 getColour() { return colour; }
	Vec2 getOrigin() { return origin; }
	Vec2 getSize();
	Vec2 getScale();
	float getRotation();
	Vec2 getPosition();
	Rect getSource();
	Rect getDestination();
	int getSpritesAcross();
	int getSpritesDown();
	
	void switchAnimationState(AnimationStates _new_state);
	void setTexture(Texture*, AnimationStates = AnimationStates::IDLE, int frames_width = 1, int frames_height = 1);
	void setScale(Vec2);
	void setRotation(float);
	void setPosition(Vec2);
	void setOrigin(Vec2);
	void setSource(Rect _source);
	void setDestination(Rect _destination);
	void setSpritesAcross(int _sprites_across);
	void setSpritesDown(int _sprites_down);

	int getFrameWidth();
	void setFrameWidth(int _frame_width);

	int getFrameHeight();
	void setFrameHeight(int _frame_height);
protected:

	int frame_width = 0.0f;
	int frame_height = 0.0f;
	int sprites_across = 1;
	int sprites_down = 1;
	Vec2 position;
	float rotation;
	Vec2 scale = Vec2(1.0f, 1.0f);
	Vec4 colour;
	Vec2 origin;
	Texture* texture;
	Rect source = Rect(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
	Rect destination = Rect(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));

	AnimationStates animation_state = AnimationStates::IDLE;

	std::map<AnimationStates, TextureData*> texture_container;
};