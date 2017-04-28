#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "GameObject.h"
#include "BaseCamera.h"

class Background : public GameObject
{
public:
	Background(Sprite* _sprite, BaseCamera * camera);
	//Background(AnimatedSprite* _sprite);
	Background(std::vector<Sprite*> _sprites, BaseCamera* camera, Vec2* position);
	//Background(std::vector<AnimatedSprite*> _sprites);
	~Background();

	virtual bool Update(float dt) override;
	virtual bool Draw() override;

protected:
	bool parallax = false;
	std::vector<Sprite*> backgrounds;
	std::vector<float> parallaxScales;
	BaseCamera* main_camera;
	Vec2 previousCamPosition;

};