#pragma once
//C++

//DXTK

//OURS
#include "..\DXTK_Wrapper\CustomMath.h"
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "../Main_Engine/GameData.h"

class Texture;
class Renderer;

enum class AnimationState
{
	NONE = 0,
	IDLE = 1,
	WALK = 2,
	RUN = 3,
	JUMP = 4,
	DEATH = 5
};

//=================================================================
// Sprite is a Texture with position scale and rotation,
//it is also the basic drawable object
//=================================================================

class Sprite
{
public:
	Sprite(Texture*);
	Sprite(std::string _fileName, Renderer* _renderer = GameData::renderer);
	virtual ~Sprite();

	virtual void Update();
	void animation(float _dt);

	Texture* GetTexture() { return texture; }
	Vec4 getColour() { return colour; }
	Vec2 getOrigin() { return origin; }
	Vec2 getSize();
	Vec2 getScale();
	float getRotation();
	Vec2 getPosition();
	int getSpriteFrameWidth();
	int getSpriteFrameHeight();
	int getFramesWide();
	int getFramesTall();
	int getFramesPerAnimation();
	int getCurrentFrame();
	Rect getDrawBox();
	AnimationState getAnimationState();

	void setTexture(Texture*);
	void setScale(Vec2);
	void setRotation(float);
	void setPosition(Vec2);
	void setOrigin(Vec2);
	void setSpriteFrameWidth(int _sprite_frame_width);
	void setSpriteFrameHeight(int _sprite_frame_height);
	void setFramesWide(int _frames_wide);
	void setFramesTall(int _frames_tall);
	void setFramesPerAnimation(int _frames_per_animation);
	void setCurrentFrame(int _frame);
	void setDrawBox(Rect _draw_box);
	void setAnimationState(AnimationState _animation_state);

protected:

	Vec2 position;
	float rotation;
	Vec2 scale;
	Vec4 colour;
	Vec2 origin;
	Texture* texture;

	float animation_tick = 0.0f;
	float animation_length = 0.5f;
	int sprite_frame_width = 0;
	int sprite_frame_height = 0;
	int frames_wide = 1;
	int frames_tall = 1;
	int frames_per_animation = 1;
	int current_frame = 1; 
	Rect draw_box;
	AnimationState animation_state = AnimationState::NONE;
};

