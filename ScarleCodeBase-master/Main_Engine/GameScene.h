#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"
#include "GameFileLoader.h"
#include "Text.h"

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
	void changeLevel();

	Player* player;
	GameFile* gameFile;
	Timer* timer;
	Text* Scoretxt;
	Text* Livestxt;
	int level_number = 0;
	int new_level_number = 0;
};