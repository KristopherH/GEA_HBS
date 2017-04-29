#pragma once
#include "../Main_Engine/GameObject.h"

class Timer : public GameObject
{

public:

	Timer();
	~Timer();

	bool Update(float dt) override;
	bool Draw() override;

	float getTime() { return time; }

private:

	float time = 0;
};