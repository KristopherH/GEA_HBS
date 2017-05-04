#pragma once
#include "Text.h"

class Timer : public Text
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