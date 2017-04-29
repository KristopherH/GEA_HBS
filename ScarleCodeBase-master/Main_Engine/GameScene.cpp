#include "GameScene.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Background.h"
#include "UI.h"
#include "Player.h"
#include "LevelLoader.h"
#include "Game_Controller.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "AnimatedSprite.h"
#include "Texture.h"
#include "Object_Factory.h"
#include "Checkpoint.h"
#include "Rope.h"
#include "Timer.h"

GameScene::GameScene()
{
	std::vector<Texture*> textures;

	player = static_cast<Player*>(ObjectFactory::createPlayer());

	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(new Vec2(-475.0f, 350.0f));
	player->setGravity(true);

	Level* level1 = LevelLoader::loadLevel("Level.txt");
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

	Background* bg = new Background(BGs, cam, level1->backgroundStartingPos);
	go_list.push_back(bg);

	player->setPosition(level1->playerStartingPosition);
	for (auto go : level1->go_list)
	{
		go_list.push_back(go);
		go = nullptr;
	}
	delete level1;

	cam->setPlayerTracker(player);

	go_list.push_back(player);

	std::vector<Sprite*> UI_objects;
	UI_objects.push_back(new Sprite("sign-3", GameData::renderer));	

	Timer* timer = new Timer();
	go_list.push_back(timer);

	UI* ui_scene = new UI(UI_objects, cam);
	go_list.push_back(ui_scene);
	return;
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);
}

void GameScene::Draw()
{
	Scene::Draw();

	GameData::renderer->renderText("Lives: " + std::to_string(GameData::player->getLives()), GameData::player->getPosition() + Vec2(620.0f, 230.0f),
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);

	GameData::renderer->renderText("Score: " + std::to_string(GameData::player->getScore()), GameData::player->getPosition() + Vec2(620.0f, 270.0f),
		Vec4(0.0f, 0.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);

	
}