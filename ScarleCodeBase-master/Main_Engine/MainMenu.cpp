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
	Button* Playbtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Play");
	Playbtn->setPosition(new Vec2(200.0f, 1200.0f));
	Playbtn->setSize(new Vec2(400.0f, 200.0f));
	Playbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Playbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("GameScene", new GameScene());
		GameData::scene_manager->setCurrentScene("GameScene");
	});
	
	Button* LevelEdbtn = new Button(new Sprite("Button", GameData::renderer), "button2", "Button", ""/*"Level Editor"*/);
	LevelEdbtn->setPosition(new Vec2(1170.0f, 1200.0f));/*&GameData::screen.Center());*/
	LevelEdbtn->setSize(new Vec2(400.0f, 200.0f));
	LevelEdbtn->setOrigin(new Vec2(0.0f, 0.0f));
	LevelEdbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("LevelEditorScene", new LevelEditorScene());
		GameData::scene_manager->setCurrentScene("LevelEditorScene");
	});

	Button* Optionsbtn = new Button(new Sprite("Button", GameData::renderer), "button3", "Button", "");//"Options");
	Optionsbtn->setPosition(new Vec2(2150.0f, 1200.0f));//new Vec2(GameData::screen.Center().x - Optionsbtn->getSize().x / 2, 400.0f)/*&GameData::screen.Center()*/);
	Optionsbtn->setSize(new Vec2(400.0f, 200.0f));
	Optionsbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Optionsbtn->setCallbackFunction([]() {
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
	go_list.push_back(Playbtn);
	//go_list.push_back(LevelEdbtn);
	//go_list.push_back(Optionsbtn);
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
	GameData::renderer->renderText("Generic Platformer \n          Engine", (cam->getPosition() + Vec2(750.0f, 350.0f)) * -1.0f,
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f, 0.0f, 3.5f);
}
