#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"
#include "GameFileLoader.h"

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
	int level_number = 0;
	int new_level_number = 0;
};