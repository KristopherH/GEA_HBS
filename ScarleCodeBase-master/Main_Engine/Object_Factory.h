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
	ROPE
};

class ObjectFactory
{
public:
	static GameObject* createPlayer();
	static GameObject* createEnemy();
	static GameObject* createPlatform();
	static GameObject* createLadder();
	static GameObject* createCollectable();
	static GameObject* createBackground();
	static GameObject* createRope();

	static void init();

	static std::map<Type, std::function<GameObject*()>> create_object;
	static std::map<Type, Texture*> texture_pool;

	//static std::map<Type, std::string> objects_sprite_names;
};