#include "PauseMenu.h"
#include "PauseOptions.h"

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

PauseMenu::PauseMenu()
{
	ResumeBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Resume");
	ResumeBtn->setSize(new Vec2(200.0f, 100.0f));
	ResumeBtn->setPosition(new Vec2(GameData::screen.Center().x - 220, 300.0f));
	ResumeBtn->setOrigin(new Vec2(0.0f, 0.0f));
	ResumeBtn->setCallbackFunction([]() {
		GameData::scene_manager->setCurrentScene("GameScene", false);
		GameData::sound_manager->stopSound();
		GameData::sound_manager->playSound("Level1-Music.wav", false, true);
	});

	OptnsBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Options");
	OptnsBtn->setSize(new Vec2(200.0f, 100.0f));
	OptnsBtn->setPosition(new Vec2(GameData::screen.Center().x - 220, ResumeBtn->getPosition().y + 150.0f));
	OptnsBtn->setOrigin(new Vec2(0.0f, 0.0f));
	OptnsBtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("PauseOptionsScene", new PauseOptions());
		GameData::scene_manager->setCurrentScene("PauseOptionsScene", false);
	});

	ExitBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Exit");
	ExitBtn->setSize(new Vec2(200.0f, 100.0f));
	ExitBtn->setPosition(new Vec2(GameData::screen.Center().x - 220, OptnsBtn->getPosition().y + 150.0f));
	ExitBtn->setOrigin(new Vec2(0.0f, 0.0f));
	ExitBtn->setCallbackFunction([]() {
		GameData::scene_manager->setCurrentScene("MainMenuScene", false);
	});

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

	GameData::renderer->renderText("Pause Menu", GameData::screen.Center() * -1 + Vec2(600.0f, 100.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 2.5f);
}
