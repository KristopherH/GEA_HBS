#include "PauseMenu.h"
#include "OptionsMenu.h"

#include "SceneManager.h"
#include "SoundManager.h"
#include "BaseCamera.h"
#include "Texture.h"
#include "MainMenu.h"
#include "GameData.h"
#include "DXTKRenderer.h"
#include "GameObject.h"
#include "Sprite.h"
#include "CustomMath.h"
#include "UI.h"
#include "Text.h"

PauseMenu::PauseMenu()
	:Scene()
{

	Text* PMtxt = new Text(nullptr, "txt", "NULL", "Pause Menu");
	PMtxt->setSize(new Vec2(800, 800));
	PMtxt->setPosition(new Vec2((GameData::currentCamera->getViewSize().x / 2) - (PMtxt->getSize().x / 2), -300.0f));
	PMtxt->setColor(Vec4(0.0f, 1.0f, 250.0f, 1.0f));

	ResumeBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Resume");
	ResumeBtn->setSize(new Vec2(200.0f, 100.0f));
	ResumeBtn->setPosition(new Vec2((GameData::currentCamera->getViewSize().x / 2) - (ResumeBtn->getSize().x / 2), 300.0f));
	ResumeBtn->setOrigin(new Vec2(0.0f, 0.0f));
	ResumeBtn->setCallbackFunction([]() {
		GameData::scene_manager->setCurrentScene("GameScene", false);
		GameData::sound_manager->stopSound();
		GameData::sound_manager->playSound("Level1-Music.wav", false, true);
	});

	OptnsBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Options");
	OptnsBtn->setSize(new Vec2(200.0f, 100.0f));
	OptnsBtn->setPosition(new Vec2((GameData::currentCamera->getViewSize().x / 2) - (OptnsBtn->getSize().x / 2),
		ResumeBtn->getPosition().y + 150.0f));
	OptnsBtn->setOrigin(new Vec2(0.0f, 0.0f));
	OptnsBtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("OptionsMenuScene", new OptionsMenu());
		GameData::scene_manager->setCurrentScene("OptionsMenuScene", false);
	});

	ExitBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Exit");
	ExitBtn->setSize(new Vec2(200.0f, 100.0f));
	ExitBtn->setPosition(new Vec2((GameData::currentCamera->getViewSize().x / 2) - (ExitBtn->getSize().x / 2),
		OptnsBtn->getPosition().y + 150.0f));
	ExitBtn->setOrigin(new Vec2(0.0f, 0.0f));
	ExitBtn->setCallbackFunction([]() {
		GameData::scene_manager->removeScene("GameScene");
		GameData::scene_manager->removeScene("PauseMenuScene");
		GameData::scene_manager->setCurrentScene("MainMenuScene", false);
	});

	go_list.push_back(PMtxt);
	go_list.push_back(ResumeBtn);
	go_list.push_back(OptnsBtn);
	go_list.push_back(ExitBtn);
}

void PauseMenu::Update(float dt)
{
	Scene::Update(dt);
}

void PauseMenu::Draw()
{

	GameData::scene_manager->getScene("GameScene")->Draw();

	Scene::Draw();
}
