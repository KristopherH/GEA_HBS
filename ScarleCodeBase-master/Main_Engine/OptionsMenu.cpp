#include "OptionsMenu.h"
#include "MainMenu.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "BaseCamera.h"
#include "Button.h"
#include "Texture.h"
#include "DXTKRenderer.h"
#include "GameObject.h"
#include "Sprite.h"
#include "CustomMath.h"
#include "UI.h"
#include "Text.h"

OptionsMenu::OptionsMenu()
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
	
	Background* bg = new Background(BGs, cam, new Vec2());

	Button* Backbtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Back");
	Backbtn->setSize(new Vec2(200.0f, 100.0f));
	Backbtn->setPosition(new Vec2(GameData::screen.Center().x + 450.0f, 0.0f));
	Backbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Backbtn->setCallbackFunction([]() {
		GameData::scene_manager->setCurrentScene("MainMenuScene", false);
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
	noticeBoard->setSize(new Vec2(1000.0f, 1000.0f));
	noticeBoard->setPosition(new Vec2(((GameData::screen.Center().x / 2) * -1),
		(GameData::screen.Center().y / 2) - (GameData::screen.Center().y * 2)));
	//go_list.push_back(noticeBoard);

	Vec2 pos(noticeBoard->getPosition());
	Vec2 size(noticeBoard->getSize().y / InputManager::key_inputs.size(),
			  noticeBoard->getSize().y / InputManager::key_inputs.size());

	for (auto input : InputManager::key_inputs)
	{
		std::string up = GameData::inputManager->ConvertToASCII(input.second);

		Button* upBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", up);
		upBtn->setSize(&size);
		upBtn->setPosition(&pos);
		upBtn->setOrigin(new Vec2(0.0f, 0.0f));
		upBtn->setCallbackFunction([]() {

			//GameData::scene_manager->setCurrentScene("MainMenuScene", false);
			//GameData::inputManager->newUpKey();
		});

		Text* txt = new Text(nullptr, "", "", InputManager::key_effect_names[input.first]);
		txt->setSize(new Vec2(200, size.y));
		txt->setPosition(&(pos + txt->getSize()));

		pos.y += size.y;
		go_list.push_back(upBtn);
		go_list.push_back(txt);


	}
}

void OptionsMenu::volumeButtons()
{
	Button* MasterPlus = new Button(new Sprite("minus-icon", GameData::renderer), "button1", "Button", "NULL");
	MasterPlus->setSize(new Vec2(50.0f, 50.0f));
	MasterPlus->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 520.0f));
	MasterPlus->setOrigin(new Vec2(0.0f, 0.0f));
	MasterPlus->setCallbackFunction([]() {
		//GameData::inputManager->newPauseKey();
	});
	Button* MasterMinus = new Button(new Sprite("plus-icon", GameData::renderer), "button1", "Button", "NULL");
	MasterMinus->setSize(new Vec2(50.0f, 50.0f));
	MasterMinus->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 520.0f));
	MasterMinus->setOrigin(new Vec2(0.0f, 0.0f));
	MasterMinus->setCallbackFunction([]() {
		//GameData::inputManager->newPauseKey();
	});

	Button* SFXPlus = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "NULL");
	SFXPlus->setSize(new Vec2(50.0f, 50.0f));
	SFXPlus->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 520.0f));
	SFXPlus->setOrigin(new Vec2(0.0f, 0.0f));
	SFXPlus->setCallbackFunction([]() {
		//GameData::inputManager->newPauseKey();
	});
	Button* SFXMinus = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "NULL");
	SFXMinus->setSize(new Vec2(50.0f, 50.0f));
	SFXMinus->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 520.0f));
	SFXMinus->setOrigin(new Vec2(0.0f, 0.0f));
	SFXMinus->setCallbackFunction([]() {
		//GameData::inputManager->newPauseKey();
	});

	//go_list.pushback();
}