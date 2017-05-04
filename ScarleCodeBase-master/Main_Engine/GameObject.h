#pragma once
//C++
#include <vector>
#include <map>

//DXTK

//OURS
#include "CustomMath.h"
#include "Sprite.h"
#include "Enum_container.h"

enum Animation
{
	IDLE,
	WALK,
	RUN,
	JUMPING,
	FALLING
};

class InputManager;
class Renderer;

class GameObject
{
public:
	//Init
	GameObject();
	GameObject(Sprite* sprite, std::string _name, std::string _tag, int _sprites_across = 1, int _sprites_down = 1);
	//GameObject(Sprite* sprite, std::string _name, std::string _tag);
	GameObject(Sprite* _sprite);
	~GameObject();

	//Updates
	virtual bool Update(float dt);
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
	std::string getType() { return type; }

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
	void setType(std::string _type) { type = _type; }

	void setGravity(bool _gravity_on) { gravity_on = _gravity_on; }
	bool setGravityTag(std::string _gravity_tag);
	bool playerrr = false;

protected:
	bool alive = true;

	Vec2 position;
	Vec2 acceleration;
	Vec2 velocity;
	Vec2 drag;
	float speed = 400;
	float max_speed = 1.0f;
	bool grounded = false;
	bool gravity_on = false;
	bool solid = true;
	const float gravity_constant = 0.01f;


	Vec2 size;
	Vec2 scale = Vec2(1.0f, 1.0f);
	Vec2 origin;
	float rotation;
	Rect bottomCollider;

	Rect box = Rect(Vec2(0, 0), Vec2(0,0));

	Direction move_direction = Direction::NONE;

	std::string tag = "GameObject";
	std::string name = "GameObject";
	std::string type = "GameObject";
	std::vector<std::string> gravity_trigger_tags;

	Sprite* sprite = nullptr;

	float animation_tick = 0.0f;
	float animation_delay = 0.1f;
	int frame_tick = 0;

	void animation(float _dt);

	Animation animation_state = Animation::IDLE;
	std::map<Animation, std::vector<Rect>> animations;
};