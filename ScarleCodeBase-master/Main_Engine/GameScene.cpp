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
#include "LevelSwitcher.h"
#include "WinScene.h"
#include "Button.h"

GameScene::GameScene()
{
	std::vector<Texture*> textures;

	timer = new Timer();
	timer->setPosition(&(GameData::currentCamera->getCameraSize() - Vec2(265.0f, 290.0f)));
	timer->setSize(new Vec2(280.0f, 100.0f));
	timer->setColor(Vec4(1, 0, 0, 1));

	player = static_cast<Player*>(ObjectFactory::createPlayer());

	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(new Vec2(-475.0f, 350.0f));
	player->setGravity(true);

	go_list.push_back(player);

	Livestxt = new Text(nullptr, "txt", "NULL", "Lives: " + std::to_string(GameData::player->getLives()));
	Livestxt->setSize(new Vec2(150, 100));
	Livestxt->setPosition(&(GameData::currentCamera->getCameraSize() - Vec2(200.0f, 250.0f)));
	Livestxt->setColor(Vec4(0.0f, 0.0f, 0.40f, 1.0f));

	Scoretxt = new Text(nullptr, "txt", "NULL", "Score: " + std::to_string(GameData::player->getScore()));
	Scoretxt->setSize(new Vec2(150, 100));
	Scoretxt->setPosition(&(GameData::currentCamera->getCameraSize() - Vec2(190.f, 215.0f)));
	Scoretxt->setColor(Vec4(0.0f, 0.40f, 0.0f, 1.0f));

	gameFile = GameFileLoader::loadGame();
	changeLevel();
}

void GameScene::Update(float dt)
{
	for (auto& go : go_list)
	{
		if (go->getType() == "LevelSwitcher")
		{
			LevelSwitcher* lvlSwitch = static_cast<LevelSwitcher*>(go);
			int newLevel = lvlSwitch->switchToNextLevel();
			if (newLevel != -1)
			{
				if (newLevel == -2)
				{
					GameData::scene_manager->addScene("WinScene", new WinScene(timer->getTime()));
					GameData::scene_manager->setCurrentScene("WinScene");
				}
				else
				{
					new_level_number = newLevel;
				}
			}
		}
	}
	if (new_level_number != level_number)
	{
		changeLevel();
	}
	Scene::Update(dt);
}

void GameScene::Draw()
{
	Livestxt->setText("Lives: " + std::to_string(GameData::player->getLives()));
	Scoretxt->setText("Lives: " + std::to_string(GameData::player->getScore()));
	
	Scene::Draw();
}

void GameScene::changeLevel()
{
	level_number = new_level_number;

	go_list.clear();
	
	if (gameFile->levels.size() <= level_number) //Level doesn't exist
		return;

	Level* level1 = &gameFile->levels[level_number];
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
	//copy level
	for (auto go : level1->go_list)
	{
		go_list.push_back(go);
		go = nullptr;
	}

	cam->setPlayerTracker(player);
	
	go_list.push_back(player);
	go_list.push_back(cam);

	Button* ui_scene = new Button(new Sprite("sign-3", GameData::renderer), "", "" , "");
	ui_scene->setCallbackFunction([]() {});
	ui_scene->setScale(new Vec2(0.2, 0.2));
	ui_scene->setPosition(new Vec2(GameData::currentCamera->getCameraSize() - ui_scene->getSize()));
	ui_scene->setScreenSpace(true);

	go_list.push_back(ui_scene);
	go_list.push_back(timer);
	go_list.push_back(Scoretxt);
	go_list.push_back(Livestxt);
	return;
}
