#pragma once
#pragma once
#include "Platform.h"
#include <string>


class FallingPlatform : public Platform
{
	friend class LevelLoader;
public:

	FallingPlatform();
	~FallingPlatform();

	bool Update(float dt) override;
	bool Draw() override;

	void setTimer(float wantedTimer) {  toFallTime =  wantedTimer; }
	float getTimer() { return toFallTime; }
	virtual void toggleEditing() override;



private:

	float toFallTime = 10;
	float fallTime = 0;
	float deadTime = 0;
	bool isFalling = false;

};