#include "MainMenu.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "BaseCamera.h"
#include "LevelEditor.h"
#include "Button.h"
#include "Texture.h"
#include "DXTKRenderer.h"
#include "Sprite.h"
#include "CustomMath.h"

MainMenuScene::MainMenuScene()
{
	Scene::Scene();
	Button* btn = new Button(new Sprite("Button", GameData::renderer), "button1", "");
	btn->setSize(new Vec2(200.0f, 100.0f));
	btn->setPosition(new Vec2(0.0f, 0.0f)/*&GameData::screen.Center()*/);
	btn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("GameScene", new GameScene());
		GameData::scene_manager->setCurrentScene("GameScene");
	});

	Button* btn1 = new Button(new Sprite("Button", GameData::renderer), "button1", "");
	btn1->setSize(new Vec2(200.0f, 100.0f));
	btn1->setPosition(new Vec2(GameData::screen.Center().x - btn1->getSize().x/2, 400.0f)/*&GameData::screen.Center()*/);
	btn1->setCallbackFunction([]() {
		GameData::scene_manager->addScene("LevelEditorScene", new LevelEditorScene());
		GameData::scene_manager->setCurrentScene("LevelEditorScene");
	});

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
	go_list.push_back(btn);
	go_list.push_back(btn1);

	//Camera
	//go_list.push_back(ObjectFactory::createBackground());
	//Background* bg = new Background(BGs, GameData::currentCamera);
	
}

void MainMenuScene::Update(float dt)
{
	//if (GameData::inputManager->getKeyHeld(Inputs::USE) ||
	//	GameData::inputManager->getMouseLeft())
	//	{
	//		GameData::scene_manager->addScene("GameScene", new GameScene());
	//		GameData::scene_manager->setCurrentScene("GameScene", true);
	//	}
	//if (GameData::inputManager->getMouseRight())
	//{
	//	GameData::scene_manager->addScene("Editor", new LevelEditorScene());
	//	GameData::scene_manager->setCurrentScene("Editor", true);
	//}
	Scene::Update(dt);
}

void MainMenuScene::Draw()
{
	Scene::Draw();
}
