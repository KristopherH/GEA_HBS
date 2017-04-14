#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"

class PlayerV2;

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:
	PlayerV2* player;
};