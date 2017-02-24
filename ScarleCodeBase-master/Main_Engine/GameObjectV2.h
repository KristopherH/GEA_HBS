#pragma once

#include "CustomMath.h"
#include "Sprite.h"
#include <vector>

class InputManager;

class GameObjectV2
{
public:
	GameObjectV2();
	GameObjectV2(Sprite* sprite, std::string _name, std::string _tag);
  GameObjectV2::GameObjectV2(Sprite* _sprite);
	~GameObjectV2();

	virtual bool Update();
	
	Vec2 GetPosition() { return position; }
	Vec2 GetSize() { return size; }
	Sprite* GetSprite() { return sprite; }
	Vec2 GetOrigin() { return origin; }
	float GetRotation() { return rotation; }
	std::string getName() { return name; }
	std::string getTag() { return tag; }

	void SetPosition(Vec2* _position) { position.x = _position->x; position.y = _position->y;}
	void SetSize(Vec2* _size) { size.x = _size->x; size.y = _size->y; }
	void SetSprite(Sprite* _sprite) { sprite = _sprite; }
	void SetOrigin(Vec2* _origin) { origin.x = _origin->x; origin.y = _origin->y;; }
	void SetRotation(float _rot) { rotation = _rot; }

	void setName(std::string _name) { name = _name; }
	void setTag(std::string _tag) { tag = _tag; }
	void setGravity(bool _gravity_on) { gravity_on = _gravity_on; }
	bool setGravityTag(std::string _gravity_tag);

	void movePosition(Vec2* _translation);
	void gravityUpdate();

protected:
	Vec2 position;
	Vec2 size;
	Vec2 origin;
	float rotation;
	bool grounded = false;
	bool gravity_on = false;

	float falling_speed = 0.0f;
	float gravity_acceleration = 0.01f;

	std::string tag = "GameObject";
	std::string name = "GameObject";
	std::vector<std::string> gravity_trigger_tags;

	Sprite* sprite = nullptr;
};