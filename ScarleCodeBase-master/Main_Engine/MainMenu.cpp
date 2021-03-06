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
#include "GameFileCreation.h"
#include "Text.h"
#include "SettingsLoader.h"

MainMenuScene::MainMenuScene()
	:Scene()
{
	SettingsLoader::loadSettings();

	Button* Playbtn = new Button(new Sprite("Button", GameData::renderer),
											"button1", "Button", "Play");
	Playbtn->setSize(new Vec2(300.0f, 150.0f));
	Playbtn->setPosition(new Vec2(GameData::currentCamera->getViewSize().x / 2 - 
						(Playbtn->getSize().x/2) - (Playbtn->getSize().x * 1.5), 700.0f));
	Playbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Playbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("GameScene", new GameScene());
		GameData::scene_manager->setCurrentScene("GameScene", false);
		GameData::sound_manager->stopSound();
		GameData::sound_manager->playSound("Level1-Music.wav", false, true);
	});

	Button* LevelEdbtn = new Button(new Sprite("Button", GameData::renderer),
											   "button2", "Button", "Level Editor");
	LevelEdbtn->setSize(new Vec2(300.0f, 150.0f));
	LevelEdbtn->setPosition(new Vec2(GameData::currentCamera->getViewSize().x / 2 -
							(LevelEdbtn->getSize().x / 2), 700.0f));
	LevelEdbtn->setOrigin(new Vec2(0.0f, 0.0f));
	LevelEdbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("GameFileCreation", new GameFileCreation());
		GameData::scene_manager->setCurrentScene("GameFileCreation", false);
	});

	Button* Optionsbtn = new Button(new Sprite("Button", GameData::renderer), 
											   "button3", "Button", "Options");
	Optionsbtn->setSize(new Vec2(300.0f, 150.0f));
	Optionsbtn->setPosition(new Vec2(GameData::currentCamera->getViewSize().x/2 - 
							(Optionsbtn->getSize().x / 2) + (Playbtn->getSize().x * 1.5), 700.0f));
	Optionsbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Optionsbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("OptionsMenuScene", new OptionsMenu());
		GameData::scene_manager->setCurrentScene("OptionsMenuScene", false);
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

	Background* bg = new Background(BGs, cam, new Vec2());

	Text* txt = new Text(nullptr, "txt", "NULL", "Generic Platformer \n          Engine");
	txt->setSize(new Vec2(GameData::currentCamera->getViewSize().x, 400));
	txt->setPosition(&((GameData::currentCamera->getViewSize() / 2) - (txt->getSize()/2)));

	go_list.push_back(bg);
	go_list.push_back(Playbtn);
	go_list.push_back(LevelEdbtn);
	go_list.push_back(Optionsbtn);
	go_list.push_back(txt);

	GameData::sound_manager->playSound("MainMenu-Music.wav", false, true);

	return;
}

void MainMenuScene::Update(float dt)
{
	Scene::Update(dt);
}

void MainMenuScene::Draw()
{
	Scene::Draw();
}