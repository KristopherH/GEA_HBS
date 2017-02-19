#pragma once

#include "CustomMath.h"
#include "Sprite.h"

class GameObjectV2
{
public:
	GameObjectV2(Sprite* sprite);
	~GameObjectV2();

	bool Update();
	
	Vec2 GetPosition() { return position; }
	Vec2 GetSize() { return size; }
	Sprite* GetSprite() { return sprite; }
	Vec2 GetOrigin() { return origin; }
	float GetRotation() { return rotation; }

	void SetPosition(Vec2* _position) { position.x = _position->x; position.y = _position->y;}
	void SetSize(Vec2* _size) { size.x = _size->x; size.y = _size->y; }
	void SetSprite(Sprite* _sprite) { sprite = _sprite; }
	void SetOrigin(Vec2* _origin) { origin.x = _origin->x; origin.y = _origin->y;; }
	void SetRotation(float _rot) { rotation = _rot; }

private:
	Vec2 position;
	Vec2 size;
	Vec2 origin;
	float rotation;

	Sprite* sprite;
};