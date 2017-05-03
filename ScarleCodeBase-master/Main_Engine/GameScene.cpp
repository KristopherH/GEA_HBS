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

GameScene::GameScene()
{
	std::vector<Texture*> textures;

	timer = new Timer();

	player = static_cast<Player*>(ObjectFactory::createPlayer());

	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(new Vec2(-475.0f, 350.0f));
	player->setGravity(true);

	go_list.push_back(player);

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
	Scene::Draw();

	GameData::renderer->renderText("Lives: " + std::to_string(GameData::player->getLives()), GameData::player->getPosition() + Vec2(620.0f, 230.0f),
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);

	GameData::renderer->renderText("Score: " + std::to_string(GameData::player->getScore()), GameData::player->getPosition() + Vec2(620.0f, 270.0f),
		Vec4(0.0f, 0.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
}

void GameScene::changeLevel()
{
	level_number = new_level_number;
	//for (auto& go : go_list)
	//{
	//	if (go->getTag() != "Player" &&
	//		go->getTag() != "Camera")
	//	{
	//		//delete go;
	//	}
	//}
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
	
	go_list.push_back(timer);
	go_list.push_back(player);
	go_list.push_back(cam);

	std::vector<Sprite*> UI_objects;
	UI_objects.push_back(new Sprite("sign-3", GameData::renderer));

	UI* ui_scene = new UI(UI_objects, cam);
	go_list.push_back(ui_scene);
	return;
}
