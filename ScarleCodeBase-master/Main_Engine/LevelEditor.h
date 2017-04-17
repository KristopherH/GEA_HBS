#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"
class Player;

class LevelEditorScene : public Scene
{
public:
	LevelEditorScene();
	virtual ~LevelEditorScene() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:
	Player* player;
};