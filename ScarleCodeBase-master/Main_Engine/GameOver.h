#pragma once

//C++

//DXTK

//OURS
#include "Scene.h"
#include "Background.h"

class GameOver : public Scene
{
public:
	GameOver();
	virtual ~GameOver() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:

};