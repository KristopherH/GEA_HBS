#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"

class Player;

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:
	Player* player;
};