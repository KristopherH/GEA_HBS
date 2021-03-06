#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"
#include <map>
class Player;
class GameObject;

enum class ObjectSelectType
{
	NONE,
	BODY, //Body is no scaling, just moving
	TOP_LEFT,
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT
}; 

enum ObjectEdge
{
	A, //Left
	B, //Top
	C, //Right
	D  //Bottom
};

class LevelEditorScene : public Scene
{
public:
	LevelEditorScene(GameFile*, int lvlNumber);
	virtual ~LevelEditorScene();

	virtual void Update(float dt) override;
	virtual void Draw() override;

	void selectObject();
	ObjectSelectType getSelectType();
	void moveObject();

	void scaleObject();

	void snap(GameObject* other, GameObject * obj);
	void toggleMode(GameObject*);


protected:
	void resetSelectedEdges();

	bool editing = true;

	std::vector<GameObject*> ui_elements;

	Player* player = nullptr;
	GameObject* obj_selected = nullptr;
	ObjectSelectType obj_select_type = ObjectSelectType::NONE;

	std::map <ObjectEdge, bool> obj_edges_selected;
	int UINum = 0;
	std::string levelName;

	GameFile* gameFile;
	int levelNumber;
};