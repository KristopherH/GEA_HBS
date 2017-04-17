#include "Object_Factory.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Background.h"
#include "GameData.h"
#include "Enemy.h"
#include "Platforms.h"
#include "Player.h"

GameObject* ObjectFactory::createPlayer()
{
	Sprite* sprite1 = new Sprite("player_sprite", GameData::renderer);
	Player* player = new Player(sprite1, "Player", "Player");
	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(new Vec2(-475.0f, 350.0f));
	player->setGravity(true);

	player->setGravityTag("Slow Platform");
	player->setGravityTag("Sticky Platform");
	player->setGravityTag("Speed Platform");
	player->setGravityTag("Conveyor Left");
	player->setGravityTag("Conveyor Right");
	player->setGravityTag("Jump Platform");
	player->setGravityTag("Standard Platform");

	return player;
}



GameObject* ObjectFactory::createEnemy()
{
	return new Enemy(new Vec2(0.0f, 0.0f), new Vec2(25.0f, 25.0f), 0.0f, "Enemy");
}



GameObject* ObjectFactory::createPlatform()
{
	GameObject* platform = new GameObject(new Sprite(Platforms::platform_sprites["Standard"]),
										  "Standard Platform", "Standard Platform");

	platform->setSize(new Vec2(70, 7));
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

	ladder->setPosition(new Vec2(0, 0));
	ladder->setSize(new Vec2(30, 150));
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
	collectible = new GameObject(collectible_spr, "Collectible", "Collectible");

	collectible->setPosition(new Vec2(0, 0));
	collectible->setSize(new Vec2(10, 10));

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
