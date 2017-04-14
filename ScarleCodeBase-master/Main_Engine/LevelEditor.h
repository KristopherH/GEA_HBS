#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"
class PlayerV2;

class LevelEditorScene : public Scene
{
public:
	LevelEditorScene();
	virtual ~LevelEditorScene() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:
	PlayerV2* player;
};