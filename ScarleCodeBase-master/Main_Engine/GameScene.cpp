#include "GameScene.h"
//C++

//DXTK

//OURS
#include "GameDataV2.h"
#include "Background.h"
#include "PlayerV2.h"
#include "LevelLoader.h"
#include "Game_Controller.h"
#include "Scene.h"

GameScene::GameScene()
{
	std::vector<Sprite*> BGs;
	BGs.push_back(new Sprite("11_background", GameDataV2::renderer));
	BGs.push_back(new Sprite("10_distant_clouds", GameDataV2::renderer));
	BGs.push_back(new Sprite("09_distant_clouds1", GameDataV2::renderer));
	BGs.push_back(new Sprite("08_clouds", GameDataV2::renderer));
	BGs.push_back(new Sprite("07_huge_clouds", GameDataV2::renderer));
	BGs.push_back(new Sprite("06_hill2", GameDataV2::renderer));
	BGs.push_back(new Sprite("05_hill1", GameDataV2::renderer));
	BGs.push_back(new Sprite("04_bushes", GameDataV2::renderer));
	BGs.push_back(new Sprite("03_distant_trees", GameDataV2::renderer));
	BGs.push_back(new Sprite("02_trees and bushes", GameDataV2::renderer));
	BGs.push_back(new Sprite("01_ground", GameDataV2::renderer));

	Background* bg = new Background(BGs, cam);
	go_list.push_back(bg);

	Sprite* sprite1 = new Sprite("player_sprite", GameDataV2::renderer);
	player = new PlayerV2(sprite1, "Player", "Player");

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

	Level* level1 = LevelLoader::loadLevel("Level.txt");
	player->setPosition(level1->playerStartingPosition);
	for (auto go : level1->go_list)
	{
		go_list.push_back(go);
		go = nullptr;
	}
	delete level1;

	cam->setPlayerTracker(player);

	go_list.push_back(player);
	return;
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);
}

void GameScene::Draw()
{
	Scene::Draw();
	GameDataV2::renderer->renderText("Lives: " + std::to_string(player->getLives()), (cam->getPosition() + Vec2(-600.0f, 450.0f)) * -1.0);
}
