#include "OptionsMenu.h"
#include "MainMenu.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "SceneManager.h"
#include "BaseCamera.h"
#include "Button.h"
#include "Texture.h"
#include "DXTKRenderer.h"
#include "Sprite.h"
#include "CustomMath.h"
#include "UI.h"
#include "Text.h"
#include "Helper.h"
#include "Object_Factory.h"

OptionsMenu::OptionsMenu()
{
	Scene::Scene();

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


	Button* Backbtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Back");
	Backbtn->setSize(new Vec2(200.0f, 100.0f));
	Backbtn->setPosition(new Vec2(GameData::screen.Center().x + 300.0f, 800.0f)/*&GameData::screen.Center()*/);
	Backbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Backbtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("MainMenuScene", new MainMenuScene());
		GameData::scene_manager->setCurrentScene("MainMenuScene");
	});	

	go_list.push_back(bg);
	go_list.push_back(Backbtn);
	keyBindings();
	volumeButtons();
}

void OptionsMenu::Update(float dt)
{
	Scene::Update(dt);
}

void OptionsMenu::Draw()
{
	Scene::Draw();
}

void OptionsMenu::keyBindings()
{
	GameObject* noticeBoard = new GameObject(new Sprite("sign-1", GameData::renderer), "button", "Button");
	noticeBoard->setSize(new Vec2(GameData::currentCamera->getCameraSize().x,
								  GameData::currentCamera->getCameraSize().y));
	noticeBoard->setPosition(new Vec2(-GameData::currentCamera->getCameraSize().x / 2,
									  -GameData::currentCamera->getCameraSize().y / 2));
	go_list.push_back(noticeBoard);

	Vec2 pos(GameData::currentCamera->getCameraSize().x / 100 * 20,
			 GameData::currentCamera->getCameraSize().y / 100 * 30);
	Vec2 size((GameData::currentCamera->getCameraSize().x / 100 * 60) / InputManager::key_inputs.size(),
			  (GameData::currentCamera->getCameraSize().y / 100 * 60) / InputManager::key_inputs.size());

	for (auto input : InputManager::key_inputs)
	{
		std::string up = GameData::inputManager->ConvertToASCII(input.second);

		Text* txt = new Text(nullptr, "", "", InputManager::key_effect_names[input.first]);
		txt->setSize(new Vec2(200, size.y));
		txt->setPosition(&pos);

		Button* btn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", up);
		btn->setSize(&size);
		btn->setPosition(new Vec2(pos.x + txt->getSize().x, pos.y));
		btn->setOrigin(new Vec2(0.0f, 0.0f));
		btn->setCallbackFunction([btn, input]() {
			GameData::inputManager->inputChangeHandler(input.first, btn);
		});

		pos.y += size.y;
		go_list.push_back(btn);
		go_list.push_back(txt);


	}
}

void OptionsMenu::volumeButtons()
{

	Vec2 pos(GameData::currentCamera->getCameraSize().x / 100 * 60,
			 GameData::currentCamera->getCameraSize().y / 100 * 30);
	Vec2 size((GameData::currentCamera->getCameraSize().x / 100 * 60) / InputManager::key_inputs.size(),
			  (GameData::currentCamera->getCameraSize().y / 100 * 60) / InputManager::key_inputs.size());

	Button* VolumeBtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
		"NameChanger", "NULL", "Volume:" + Helper::to_string_with_precision(GameData::sound_manager->getMasterVolume()));
	VolumeBtn->setSize(&size);
	VolumeBtn->setPosition(&pos);
	VolumeBtn->setCallbackFunction([this, VolumeBtn]()
	{
		return;
	});
	go_list.push_back(VolumeBtn);

	Button* plusVolume = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
		"NameChanger", "NULL", "", false);
	plusVolume->setSize(new Vec2(size.y, size.y));
	plusVolume->setPosition(new Vec2(pos.x + VolumeBtn->getSize().x, pos.y));
	plusVolume->setCallbackFunction([this, VolumeBtn]()
	{
		GameData::sound_manager->setMasterVolume(GameData::sound_manager->getMasterVolume() + 1);
		VolumeBtn->setText("Volume:" + Helper::to_string_with_precision(GameData::sound_manager->getMasterVolume()));
		return;
	});
	go_list.push_back(plusVolume);

	Button* minusVolume = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
		"NameChanger", "NULL", "", false);
	minusVolume->setSize(new Vec2(size.y, size.y));
	minusVolume->setPosition(new Vec2(pos.x - minusVolume->getSize().x, pos.y));
	minusVolume->setCallbackFunction([this, VolumeBtn]()
	{
		GameData::sound_manager->setMasterVolume(max(0, GameData::sound_manager->getMasterVolume() - 1));
		VolumeBtn->setText("Volume:" + Helper::to_string_with_precision(GameData::sound_manager->getMasterVolume()));
		return;
	});
	go_list.push_back(minusVolume);

	pos.y += size.y;

	Button* SFXBtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
		"NameChanger", "NULL", "SFX:" + Helper::to_string_with_precision(GameData::sound_manager->getSFXVolume()));
	SFXBtn->setSize(&size);
	SFXBtn->setPosition(&pos);
	SFXBtn->setCallbackFunction([this, SFXBtn]()
	{
		return;
	});
	go_list.push_back(SFXBtn);

	Button* plusSFX = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
		"NameChanger", "NULL", "", false);
	plusSFX->setSize(new Vec2(size.y, size.y));
	plusSFX->setPosition(new Vec2(pos.x + VolumeBtn->getSize().x, pos.y));
	plusSFX->setCallbackFunction([this, SFXBtn]()
	{
		GameData::sound_manager->setSFXVolume(GameData::sound_manager->getSFXVolume() + 1);
		SFXBtn->setText("SFX:" + Helper::to_string_with_precision(GameData::sound_manager->getSFXVolume()));
		return;
	});
	go_list.push_back(plusSFX);

	Button* minusSFX = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
		"NameChanger", "NULL", "", false);
	minusSFX->setSize(new Vec2(size.y, size.y));
	minusSFX->setPosition(new Vec2(pos.x - minusSFX->getSize().x, pos.y));
	minusSFX->setCallbackFunction([this, SFXBtn]()
	{
		GameData::sound_manager->setSFXVolume(max(0, GameData::sound_manager->getSFXVolume() - 1));
		SFXBtn->setText("SFX:" + Helper::to_string_with_precision(GameData::sound_manager->getSFXVolume()));
		return;
	});
	go_list.push_back(minusSFX);
	
}