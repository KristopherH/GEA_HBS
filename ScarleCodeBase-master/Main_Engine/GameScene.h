#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"

class Timer;
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
	GameFile* gameFile;
	Timer* timer;
	int level_number = 0;
	int new_level_number = 0;
};