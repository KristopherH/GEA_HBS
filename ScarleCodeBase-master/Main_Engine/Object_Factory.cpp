#include "Object_Factory.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Background.h"
#include "GameData.h"
#include "Enemy.h"
#include "Platform.h"
#include "Player.h"
#include "Collectible.h"
#include "Rope.h"
//#ifdef _DXTK_
#include "Texture.h"
//#endif


std::map<Type, std::function<GameObject*()>> ObjectFactory::create_object;
std::map<Type, Texture*> ObjectFactory::texture_pool;

GameObject* ObjectFactory::createPlayer()
{
	Sprite* sprite1 = new Sprite("player_sprite", GameData::renderer);
	Player* player = new Player(sprite1, "Player", "Player");
	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(new Vec2(-475.0f, 350.0f));
	player->setGravity(true);

	player->setGravityTag("SlowPlatform");
	player->setGravityTag("StickyPlatform");
	player->setGravityTag("SpeedPlatform");
	player->setGravityTag("ConveyorLeft");
	player->setGravityTag("ConveyorRight");
	player->setGravityTag("JumpPlatform");
	player->setGravityTag("StandardPlatform");

	GameData::player = player;

	return player;
}



GameObject* ObjectFactory::createEnemy()
{
	Enemy* enemy = new Enemy(new Vec2(0.0f, 0.0f), new Vec2(100.0f, 100.0f), 0.0f, "Enemy");
	enemy->setType("Enemy");
	return enemy;
}



GameObject* ObjectFactory::createPlatform()
{
	GameObject* platform = Platform::create(STANDARD);

	platform->setSize(new Vec2(100.0f, 100.0f));
	platform->setPosition(new Vec2(0, 0));

	return platform;
}



GameObject* ObjectFactory::createLadder()
{
	Sprite* ladder_spr;
	GameObject* ladder;
	ladder_spr = nullptr;
	ladder = nullptr;

	ladder_spr = new Sprite("Ladder", GameData::renderer);
	ladder = new GameObject(ladder_spr, "Ladder", "Climbable");
	ladder->setType("Ladder");

	ladder->setPosition(new Vec2(0, 0));
	ladder->setSize(new Vec2(100.0f, 300.0f));
	ladder->setSolid(false);

	return ladder;
}



GameObject* ObjectFactory::createCollectable()
{
	Sprite* collectible_spr;
	GameObject* collectible;
	collectible_spr = nullptr;
	collectible = nullptr;

	collectible_spr = new Sprite("coin", GameData::renderer);
	collectible = new Collectible(new Vec2(0, 0), new Vec2(100.0f, 100.0f), 0, "Collectible");
	collectible->setType("Collectible");

	return collectible;
}



GameObject* ObjectFactory::createBackground()
{
	std::vector<Sprite*> BGs;
	BGs.push_back(new Sprite("11_background", GameData::renderer));
	BGs.push_back(new Sprite("10_distant_clouds", GameData::renderer));
	BGs.push_back(new Sprite("09_distant_clouds1", GameData::renderer));
	BGs.push_back(new Sprite("08_clouds", GameData::renderer));
	BGs.push_back(new Sprite("07_huge_clouds", GameData::renderer));
	BGs.push_back(new Sprite("06_hill2", GameData::renderer));
	BGs.push_back(new Sprite("05_hill1", GameData::renderer));
	BGs.push_back(new Sprite("04_bushes", GameData::renderer));
	BGs.push_back(new Sprite("03_distant_trees", GameData::renderer));
	BGs.push_back(new Sprite("02_trees and bushes", GameData::renderer));
	BGs.push_back(new Sprite("01_ground", GameData::renderer));

	Background* bg = new Background(BGs, GameData::currentCamera);

	return bg;
}

GameObject * ObjectFactory::createRope()
{
	return new Rope(Vec2(0.0f, 0.0f), ObjectFactory::texture_pool[ROPE], 10, 20.0f, 80.0f, 1.5f);
}

void ObjectFactory::init()
{
	ObjectFactory::create_object[PLATFORM] = createPlatform;
	ObjectFactory::create_object[ENEMY] = createEnemy;
	//create_object[PLAYER] = createPlayer;
	ObjectFactory::create_object[LADDER] = createLadder;
	ObjectFactory::create_object[COLLECTIBLE] = createCollectable;
	ObjectFactory::create_object[ROPE] = createRope;
	//create_object[BACKGROUND] = createBackground;

	ObjectFactory::texture_pool[PLATFORM] = new Texture("StandardPlatform", GameData::renderer);
	ObjectFactory::texture_pool[ENEMY] = new Texture("enemy_sprite", GameData::renderer);
	ObjectFactory::texture_pool[LADDER] = new Texture("Ladder", GameData::renderer);
	ObjectFactory::texture_pool[COLLECTIBLE] = new Texture("coin", GameData::renderer);
	ObjectFactory::texture_pool[ROPE] = new Texture("Rope", GameData::renderer);;
}
