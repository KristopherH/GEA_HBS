#pragma once
#include "Scene.h"

class WinScene : public Scene
{
public:
	WinScene(float timeTaken);
	~WinScene();

private:
	float timeTaken;
};