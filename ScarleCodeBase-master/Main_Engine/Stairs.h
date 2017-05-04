#pragma once
#include "EditableGameObject.h"

class Stairs : public EditableGameObject
{
	friend class LevelLoader;
public:

	Stairs(Sprite * _sprite);
	~Stairs();

	bool Update(float dt) override;
	bool Draw() override;

	virtual void toggleEditing() override;

	void setDirectionLeft(bool _left);

private:

	bool left = false;
};