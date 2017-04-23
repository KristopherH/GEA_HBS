#pragma once
#include <string>
#include <map>
#include <functional>
class GameObject;
class Texture;
//
//using Object_Type = std::string;
//
//struct ObjectTypes
//{
//	static Object_Type Player;
//	static Object_Type Enemy;
//	static Object_Type Platform;
//	static Object_Type Ladder;
//	static Object_Type Collectible;
//	static Object_Type Background;
//};
//
//Object_Type ObjectTypes::Player = "player_sprite";
//Object_Type ObjectTypes::Enemy = "enemy_sprite";
//Object_Type ObjectTypes::Platform = "StandardPlatform";
//Object_Type ObjectTypes::Ladder = "Ladder";
//Object_Type ObjectTypes::Collectible = "coin";
//Object_Type ObjectTypes::Background = "02_trees and bushes";

enum Type
{
	PLATFORM,
	ENEMY,
	PLAYER,
	LADDER,
	COLLECTIBLE,
	BACKGROUND
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

	static void init();

	static std::map<Type, std::function<GameObject*()>> create_object;
	static std::map<Type, Texture*> texture_pool;

	//static std::map<Type, std::string> objects_sprite_names;
};