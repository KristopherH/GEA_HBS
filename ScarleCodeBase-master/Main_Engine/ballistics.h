#pragma once
#include "../Main_Engine/GameObject.h"

enum BulletDirecton : INT32
{
	BD_START = 0,
	BD_UP = 1,
	BD_DOWN = 2,
	BD_RIGHT = 3,
	BD_LEFT = 4,
	BD_Target = 5,
	BD_NONE = 6,
	BD_END = 7
};

class Ballistics : public GameObject
{

public:

	Ballistics(BulletDirecton _BD);
	~Ballistics();

	bool Update(float dt) override;
	bool Draw() override;
	void setBulletSpeed(float wantedSpeed) { bulletSpeed = wantedSpeed; }
	float getBulletSpeed() { return bulletSpeed; }




private:
	float bulletSpeed;
	BulletDirecton BD;
	float timer = 0;
};