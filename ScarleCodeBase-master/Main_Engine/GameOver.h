#pragma once
#include "GameObject.h"
//C++

//DXTK

//OURS
#include "Scene.h"

class GameOver : public Scene
{
public:
	GameOver();
	virtual ~GameOver() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:

};