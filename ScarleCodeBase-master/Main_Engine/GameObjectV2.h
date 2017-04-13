#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "CustomMath.h"
#include "../DXTK_Wrapper/Sprite.h"
#include "Enum_container.h"

class InputManager;
class Renderer;

class GameObjectV2
{
public:
	//Init
	GameObjectV2();
	GameObjectV2(Sprite* sprite, std::string _name, std::string _tag);
	GameObjectV2(Sprite* _sprite);
	~GameObjectV2();

	//Updates
	virtual bool Update();
	virtual bool Draw();
	void gravityUpdate();
	void movePosition(Vec2* _translation);

	//Getters
	virtual Direction getMovementDirection();
	bool getSolid();
	bool getAlive() { return alive; }
	Vec2 getPosition();
	Vec2 getSize();
	Vec2 getScale();
	Vec2 getOrigin();
	Sprite* getSprite();
	float getRotation();
	std::string getName();
	std::string getTag();
	Rect getBox();

	//Setters
	virtual void setMovementDirection(Direction _movement_direction) { move_direction = _movement_direction; }
	void setSolid(bool _solid);
	
	void setPosition(Vec2* _position);
	void setSize(Vec2* _size);
	void setScale(Vec2* _scale) { scale.x = _scale->x; scale.y = _scale->y; }
	void setOrigin(Vec2* _origin) { origin.x = _origin->x; origin.y = _origin->y; }
	void setSprite(Sprite* _sprite) { sprite = _sprite; }
	void setRotation(float _rot) { rotation = _rot; }
	void setName(std::string _name) { name = _name; }
	void setTag(std::string _tag) { tag = _tag; }

	void setGravity(bool _gravity_on) { gravity_on = _gravity_on; }
	bool setGravityTag(std::string _gravity_tag);


protected:
	bool alive = true;

	Vec2 position;
	Vec2 acceleration;
	Vec2 velocity;
	Vec2 drag;
	float max_speed = 1.0f;
	bool grounded = false;
	bool gravity_on = false;
	bool solid = true;
	const float gravity_constant = 0.01f;

	Vec2 scale;
	Vec2 origin;
	float rotation;
	Rect bottomCollider;

	Rect box = Rect(Vec2(0, 0), Vec2(0,0));

	Direction move_direction = Direction::NONE;

	std::string tag = "GameObject";
	std::string name = "GameObject";
	std::vector<std::string> gravity_trigger_tags;

	Sprite* sprite = nullptr;
};