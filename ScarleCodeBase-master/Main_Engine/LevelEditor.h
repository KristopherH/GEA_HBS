#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"
class Player;
class GameObject;

class LevelEditorScene : public Scene
{
public:
	LevelEditorScene();
	virtual ~LevelEditorScene() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

	void selectObject();
	void moveObject();

protected:
	Player* player = nullptr;
	GameObject* obj_selected = nullptr;
};