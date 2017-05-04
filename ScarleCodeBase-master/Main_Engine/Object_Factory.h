#pragma once
#include <string>
#include <map>
#include <functional>
class GameObject;
class Texture;

enum Type
{
	PLATFORM,
	ENEMY,
	PLAYER,
	LADDER,
	COLLECTIBLE,
	BACKGROUND,
	ROPE,
	CHECKPOINT,
	MOVING_PLATFORM,
	LEVEL_SWITCHER,
	BUTTON,
	BUTTON_PLUS,
	BUTTON_MINUS,
	GUN,
	FALLING_PLATFORM
};

class ObjectFactory
{
public:
	static GameObject* createPlayer();
	static GameObject* createEnemy();
	static GameObject* createPlatform();
	static GameObject* createMovingPlatform();
	static GameObject* createLadder();
	static GameObject* createCollectable();
	static GameObject* createBackground(Vec2* pos);
	static GameObject* createRope();
	static GameObject* createCheckpoint();
	static GameObject* createLevelSwitcher();
	static GameObject* createGun();
	static GameObject* createFallingPlatform();

	static void init();

	static std::map<Type, std::function<GameObject*()>> create_object;
	static std::map<Type, Texture*> texture_pool;
	static std::map<Type, std::string> names;

	//static std::map<Type, std::string> objects_sprite_names;
};