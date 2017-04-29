#pragma once
#include "../Main_Engine/GameObject.h"

enum BulletDirecton
{
	BD_UP = 1,
	BD_DOWN = 2,
	BD_RIGHT = 3,
	BD_LEFT = 4,
	BD_Target = 5,

};

class Ballistics : public GameObject
{

public:

	Ballistics();
	~Ballistics();

	bool Update(float dt) override;
	bool Draw() override;

private:

	BulletDirecton _BD;
	float speed = 0.05;
	float timer = 0;
};