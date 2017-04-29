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

	GameObject* noticeBoard = new GameObject(new Sprite("sign-1", GameData::renderer), "button10", "Button");
	noticeBoard->setSize(new Vec2(1000.0f, 1000.0f));
	noticeBoard->setPosition(new Vec2(((GameData::screen.Center().x/2) * -1), 
		(GameData::screen.Center().y / 2) - (GameData::screen.Center().y * 2)));

	go_list.push_back(bg);
	go_list.push_back(Backbtn);
	go_list.push_back(noticeBoard);
}

void OptionsMenu::Update(float dt)
{
	Scene::Update(dt);
}

void OptionsMenu::Draw()
{
	Scene::Draw();
	
	GameData::renderer->renderText("Options Menu", GameData::screen.Center() * -1 + Vec2(600.0f, 800.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 2.5f);
}