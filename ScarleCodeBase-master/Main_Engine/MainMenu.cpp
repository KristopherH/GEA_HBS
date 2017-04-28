#include "MainMenu.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "BaseCamera.h"
#include "LevelEditor.h"
#include "OptionsMenu.h"
#include "SoundManager.h"
#include "Button.h"
#include "Texture.h"
#include "DXTKRenderer.h"
#include "Sprite.h"
#include "CustomMath.h"

MainMenuScene::MainMenuScene()
{
	Scene::Scene();
	Button* Playbtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Play");
	Playbtn->setSize(new Vec2(300.0f, 150.0f));
	Playbtn->setPosition(new Vec2(GameData::screen.Center().x - 800.0f, 700.0f));
	Playbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Playbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("GameScene", new GameScene());
		GameData::scene_manager->setCurrentScene("GameScene");
		GameData::sound_manager->stopSound();
		GameData::sound_manager->playSound("Level1-Music.wav", false, true);
	});

	Button* LevelEdbtn = new Button(new Sprite("Button", GameData::renderer), "button2", "Button", "Level Editor");
	LevelEdbtn->setSize(new Vec2(300.0f, 150.0f));
	LevelEdbtn->setPosition(new Vec2(GameData::screen.Center().x + 200.0f, 700.0f));/*&GameData::screen.Center());*/
	LevelEdbtn->setOrigin(new Vec2(0.0f, 0.0f));
	LevelEdbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("LevelEditorScene", new LevelEditorScene());
		GameData::scene_manager->setCurrentScene("LevelEditorScene");
	});

	Button* Optionsbtn = new Button(new Sprite("Button", GameData::renderer), "button3", "Button", "Options");
	Optionsbtn->setSize(new Vec2(300.0f, 150.0f));
	Optionsbtn->setPosition(new Vec2(GameData::screen.Center().x - 300.0f, 700.0f)/*&GameData::screen.Center()*/);
	Optionsbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Optionsbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("OptionsMenuScene", new OptionsMenu());
		GameData::scene_manager->setCurrentScene("OptionsMenuScene");
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
	go_list.push_back(LevelEdbtn);
	go_list.push_back(Optionsbtn);

	GameData::sound_manager->setMasterVoume(100.0f);
	GameData::sound_manager->setSFXVoume(1.0f);
	GameData::sound_manager->playSound("MainMenu-Music.wav", false, true);
}

void MainMenuScene::Update(float dt)
{
	Scene::Update(dt);
}

void MainMenuScene::Draw()
{
	Scene::Draw();
	GameData::renderer->renderText("Generic Platformer \n          Engine", Vec2((GameData::screen.Center().x / 2) * -1, (GameData::screen.Center().y / 2) * -1),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 2.5f);
}
