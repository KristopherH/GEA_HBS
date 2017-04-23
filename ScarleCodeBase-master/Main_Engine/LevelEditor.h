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
	virtual ~LevelEditorScene();

	virtual void Update(float dt) override;
	virtual void Draw() override;

	void selectObject();
	void moveObject();
	void snap(GameObject* other, GameObject * obj);
	void toggleMode(GameObject*);

protected:
	std::vector<GameObject*> ui_elements;

	Player* player = nullptr;
	GameObject* obj_selected = nullptr;
};