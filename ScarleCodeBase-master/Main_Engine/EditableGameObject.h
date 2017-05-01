#pragma once
#include <vector>
#include "GameObject.h"

class EditableGameObject : public GameObject
{
	friend class LevelEditorScene;
public:
	EditableGameObject();
	EditableGameObject(Sprite* sprite, std::string _name, std::string _tag);
	EditableGameObject(Sprite* _sprite);
	EditableGameObject(std::vector<Sprite*> _sprite);
	virtual ~EditableGameObject();

	virtual bool Update(float dt) override;
	virtual bool Draw() override;

	virtual void toggleEditing();

	virtual void movePosition(Vec2* _translation) override;
	virtual void setPosition(Vec2* _pos) override;

protected:
	std::vector<GameObject*> ui_elements;
	bool editing;
	bool reToggleEditing = false;
};