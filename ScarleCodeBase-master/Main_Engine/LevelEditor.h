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

protected:
	std::vector<GameObject*> ui_elements;
	std::vector<std::string> creatableObjectTypes = { "StandardPlatform", "Ladder", "enemy_sprite", "coin" };

	Player* player = nullptr;
	GameObject* obj_selected = nullptr;
};