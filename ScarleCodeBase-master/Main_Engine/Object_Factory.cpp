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
#include "Checkpoint.h"
#include "MovingPlatform.h"
#include "LevelSwitcher.h"
#include "Gun.h"
#include "FallingPlatform.h"

//#ifdef _DXTK_
#include "Texture.h"
//#endif


std::map<Type, std::function<GameObject*()>> ObjectFactory::create_object;
std::map<Type, Texture*> ObjectFactory::texture_pool;
std::map<Type, std::string> ObjectFactory::names;

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
	player->getSprite()->GetTexture()->LoadPixelMap();
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

	platform->setType("Platform");
	platform->setSize(new Vec2(100.0f, 100.0f));
	platform->setPosition(new Vec2(0, 0));

	return platform;
}

GameObject* ObjectFactory::createMovingPlatform()
{
	GameObject* platform = MovingPlatform::create(STANDARD);

	platform->setType("MovingPlatform");
	platform->setSize(new Vec2(100.0f, 100.0f));
	platform->setPosition(new Vec2(0, 0));

	return platform;
}

GameObject* ObjectFactory::createLadder()
{
	Sprite* ladder_spr;
	EditableGameObject* ladder;
	ladder_spr = nullptr;
	ladder = nullptr;

	ladder_spr = new Sprite(texture_pool[LADDER]);
	ladder = new EditableGameObject(ladder_spr, "Ladder", "Climbable");
	ladder->setType("Ladder");

	ladder->setPosition(new Vec2(0, 0));
	ladder->setSize(new Vec2(100.0f, 300.0f));
	ladder->setSolid(false);

	return ladder;
}



GameObject* ObjectFactory::createCollectable()
{
	EditableGameObject* collectible;
	collectible = nullptr;

	collectible = new Collectible(new Sprite(texture_pool[COLLECTIBLE]), new Vec2(0, 0), new Vec2(100.0f, 100.0f), 0, "Collectible");
	return collectible;
}



GameObject* ObjectFactory::createBackground(Vec2* position)
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

	Background* bg = new Background(BGs, GameData::currentCamera, position);

	return bg;
}

GameObject * ObjectFactory::createRope()
{
	return new Rope(Vec2(0.0f, 0.0f), ObjectFactory::texture_pool[ROPE], 10, 20.0f, 80.0f, 1.5f, Vec2(20, 100), GameData::go_list);
}

GameObject * ObjectFactory::createCheckpoint()
{
	return new Checkpoint(new Sprite(texture_pool[CHECKPOINT]));
}
GameObject * ObjectFactory::createGun()
{
	return new Gun();
}
GameObject * ObjectFactory::createFallingPlatform()
{
	return new FallingPlatform();
}

GameObject * ObjectFactory::createLevelSwitcher()
{
	return new LevelSwitcher(new Sprite(texture_pool[LEVEL_SWITCHER]), nullptr);
}


void ObjectFactory::init()
{
	ObjectFactory::create_object[PLATFORM] = createPlatform;
	ObjectFactory::create_object[MOVING_PLATFORM] = createMovingPlatform;
	ObjectFactory::create_object[ENEMY] = createEnemy;
	ObjectFactory::create_object[LADDER] = createLadder;
	ObjectFactory::create_object[COLLECTIBLE] = createCollectable;
	ObjectFactory::create_object[ROPE] = createRope;
	ObjectFactory::create_object[CHECKPOINT] = createCheckpoint;
	ObjectFactory::create_object[LEVEL_SWITCHER] = createLevelSwitcher;
	ObjectFactory::create_object[GUN] = createGun;
	ObjectFactory::create_object[FALLING_PLATFORM] = createFallingPlatform;


	ObjectFactory::texture_pool[PLATFORM] = new Texture("StandardPlatform", GameData::renderer);
	ObjectFactory::texture_pool[MOVING_PLATFORM] = new Texture("SpeedPlatform", GameData::renderer);
	ObjectFactory::texture_pool[ENEMY] = new Texture("enemy_sprite", GameData::renderer);
	ObjectFactory::texture_pool[LADDER] = new Texture("Ladder", GameData::renderer);
	ObjectFactory::texture_pool[COLLECTIBLE] = new Texture("coin", GameData::renderer);
	ObjectFactory::texture_pool[ROPE] = new Texture("Rope", GameData::renderer);
	ObjectFactory::texture_pool[CHECKPOINT] = new Texture("sign-2", GameData::renderer);
	ObjectFactory::texture_pool[BUTTON] = new Texture("Button", GameData::renderer);
	ObjectFactory::texture_pool[BUTTON_MINUS] = new Texture("minus-icon", GameData::renderer);
	ObjectFactory::texture_pool[BUTTON_PLUS] = new Texture("plus-icon", GameData::renderer);
	ObjectFactory::texture_pool[LEVEL_SWITCHER] = new Texture("Door", GameData::renderer);
	ObjectFactory::texture_pool[GUN] = new Texture("Cannon", GameData::renderer);
	ObjectFactory::texture_pool[FALLING_PLATFORM] = new Texture("StandardPlatform", GameData::renderer);

	ObjectFactory::texture_pool[COLLECTIBLE]->LoadPixelMap();

	ObjectFactory::names[PLATFORM] = "Platform";
	ObjectFactory::names[MOVING_PLATFORM] = "Moving\nPlatform";
	ObjectFactory::names[ENEMY] = "Enemy";
	ObjectFactory::names[LADDER] = "Ladder";
	ObjectFactory::names[COLLECTIBLE] = "Collectible";
	ObjectFactory::names[ROPE] = "Rope";
	ObjectFactory::names[CHECKPOINT] = "Checkpoint";
	ObjectFactory::names[LEVEL_SWITCHER] = "Level\nSwitcher";
	ObjectFactory::names[GUN] = "Cannon";
	ObjectFactory::names[FALLING_PLATFORM] = "StandardPlatform";
}
