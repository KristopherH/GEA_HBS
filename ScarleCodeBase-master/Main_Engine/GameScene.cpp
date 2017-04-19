#include "GameScene.h"
//C++

//DXTK
#if defined _DXTK_
#include "../DXTK_Wrapper/Texture.h"
#include "../DXTK_Wrapper/LevelLoader.h"

#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/Texture.h"
#include "../Phyre/Code/LevelLoader.h"
#endif

//OURS
#include "GameData.h"
#include "Background.h"
#include "Player.h"

#include "Game_Controller.h"
#include "Scene.h"
#include "AnimatedSprite.h"


GameScene::GameScene()
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

	Background* bg = new Background(BGs, cam);
	go_list.push_back(bg);

	std::vector<Texture*> textures;

	/*textures.push_back(new Texture("SlowPlatform", GameData::renderer));
	textures.push_back(new Texture("SpeedPlatform", GameData::renderer));*/

	Sprite* sprite1 = new Sprite("player_sprite", GameData::renderer); //new AnimatedSprite(textures);
	player = new Player(sprite1, "Player", "Player");

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
	//GameData::renderer->renderText("Lives: " + std::to_string(player->getLives()), (cam->getPosition() + Vec2(-600.0f, 450.0f)) * -1.0);
}
