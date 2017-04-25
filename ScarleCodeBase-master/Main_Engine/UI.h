#pragma once

//C++
#include <vector>

//DXTK

//OURS
#include "GameObject.h"
#include "BaseCamera.h"

class UI : public GameObject
{
public:
	UI(Sprite* _sprite, BaseCamera * camera);
	UI(std::vector<Sprite*> UI_Sprites, BaseCamera* camera);
	~UI();

	virtual bool Update(float dt) override;
	virtual bool Draw() override;

protected:
	
	std::vector<Sprite*> UIElements;
	BaseCamera* main_camera;
};

