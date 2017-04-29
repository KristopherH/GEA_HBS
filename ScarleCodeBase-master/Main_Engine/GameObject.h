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
	GameObject(std::vector<Sprite*> _sprite);
	virtual ~GameObject();
  
	//Updates
	virtual bool Update(float dt);
	virtual bool Draw();
	virtual void gravityUpdate();
	virtual void movePosition(Vec2* _translation);

	//Getters
	virtual Direction getMovementDirection();
	bool getSolid();
	bool getAlive() { return alive; }
	virtual Vec2 getPosition();
	virtual Vec2 getSize();
	virtual Vec2 getScale();
	virtual Vec2 getOrigin();
	virtual Sprite* getSprite();
	virtual float getRotation();
	std::string getName();
	std::string getTag();
	Rect getBox();
	std::string getType() { return type; }

	//Setters
	virtual void setMovementDirection(Direction _movement_direction) { move_direction = _movement_direction; }
	void setSolid(bool _solid);
	
	virtual void setPosition(Vec2* _position);
	virtual void setSize(Vec2* _size);
	virtual void setScale(Vec2* _scale) { scale.x = _scale->x; scale.y = _scale->y; }
	virtual void setOrigin(Vec2* _origin) { origin.x = _origin->x; origin.y = _origin->y; }
	void setSprite(Sprite* _sprite) { sprite = _sprite; }
	void setRotation(float _rot) { rotation = _rot; }
	void setName(std::string _name) { name = _name; }
	void setTag(std::string _tag) { tag = _tag; }
	void setType(std::string _type) { type = _type; }

	void setGravity(bool _gravity_on) { gravity_on = _gravity_on; }
	bool setGravityTag(std::string _gravity_tag);
	Vec2 velocity;
	Vec2 acceleration;

protected:
	bool alive = true;

	bool physics = true;
	Vec2 position;

	Vec2 drag;
	float speed = 400;
	float max_speed = 1.0f;
	bool grounded = false;
	bool gravity_on = false;
	bool solid = true;
	const float gravity_constant = 0.03f;


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
	std::map<Animation, std::vector<Rect>> animations; //This ain't being used but leave
	std::vector<Sprite*> vectorSprites;
};