#include "GameOver.h"
//C++

//DXTK

//OURS
#include "MainMenu.h"
#include "GameData.h"
#include "player.h"
#include "Input_Manager.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "BaseCamera.h"
#include "LevelEditor.h"
#include "OptionsMenu.h"
#include "SoundManager.h"
#include "Texture.h"
#include "DXTKRenderer.h"
#include "Sprite.h"
#include "CustomMath.h"
#include "GameFileCreation.h"
#include "Object_Factory.h"
#include "Text.h"

GameOver::GameOver()
	:Scene()
{		
	GameObject* go = new GameObject(new Sprite("GO_BG2", GameData::renderer));
	go->setSize(&GameData::currentCamera->getCameraSize());
	go->setPosition(&((GameData::currentCamera->getCameraSize()/2)*-1));
	go_list.push_back(go);
	
	Text* GOtxt = new Text(nullptr, "txt", "NULL", /*"    oh dear! \n */"Game Over");
	GOtxt->setSize(new Vec2(800, 800));
	GOtxt->setPosition(new Vec2((GameData::currentCamera->getViewSize().x / 2) - (GOtxt->getSize().x / 2), -70.0f));
	GOtxt->setColor(Vec4(0.60f, 0.0f, 0.0f, 1.0f));

	Text* Scoretxt = new Text(nullptr, "txt", "NULL", "Final score: " + std::to_string(GameData::player->getScore()));
	Scoretxt->setSize(new Vec2(450, 450));
	Scoretxt->setPosition(new Vec2((GameData::currentCamera->getViewSize().x / 2) - (Scoretxt->getSize().x / 2), 295.0f));
	Scoretxt->setColor(Vec4(0.0f, 0.0f, 0.60f, 1.0f));

	Button* menuBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Main Menu");
	menuBtn->setSize(new Vec2(300.0f, 150.0f));
	menuBtn->setPosition(new Vec2((GameData::currentCamera->getViewSize().x / 2) - (menuBtn->getSize().x / 2), 700.0f));
	menuBtn->setOrigin(new Vec2(0.0f, 0.0f));
	menuBtn->setColor(Vec4(0.0f, 0.0f, 0.60f, 1.0f));
	menuBtn->setCallbackFunction([]() {
	GameData::scene_manager->setCurrentScene("MainMenuScene", false);
	});
	go_list.push_back(menuBtn);
	go_list.push_back(GOtxt);
	go_list.push_back(Scoretxt);
}

void GameOver::Update(float dt)
{
	Scene::Update(dt);
}

void GameOver::Draw()
{
	Scene::Draw();
}


