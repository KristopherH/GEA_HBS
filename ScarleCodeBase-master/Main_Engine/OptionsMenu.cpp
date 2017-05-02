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

	GameObject* noticeBoard = new GameObject(new Sprite("sign-1", GameData::renderer), "button", "Button");
	noticeBoard->setSize(new Vec2(1000.0f, 1000.0f));
	noticeBoard->setPosition(new Vec2(((GameData::screen.Center().x/2) * -1), 
		(GameData::screen.Center().y / 2) - (GameData::screen.Center().y * 2)));

	go_list.push_back(bg);
	go_list.push_back(Backbtn);
	go_list.push_back(noticeBoard);
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
	optionsText();
}

void OptionsMenu::optionsText()
{
	GameData::renderer->renderText("Up", GameData::screen.Center() * -1 + Vec2(660.0f, 280.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
	GameData::renderer->renderText("Down", GameData::screen.Center() * -1 + Vec2(660.0f, 330.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
	GameData::renderer->renderText("Left", GameData::screen.Center() * -1 + Vec2(660.0f, 400.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
	GameData::renderer->renderText("Right", GameData::screen.Center() * -1 + Vec2(660.0f, 450.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
	GameData::renderer->renderText("Jump", GameData::screen.Center() * -1 + Vec2(660.0f, 520.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
	GameData::renderer->renderText("Pause", GameData::screen.Center() * -1 + Vec2(660.0f, 570.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
	GameData::renderer->renderText("Options Menu", GameData::screen.Center() * -1 + Vec2(600.0f, 800.0f),
		Vec4(0.0f, 1.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 2.5f);
}

void OptionsMenu::keyBindings()
{
	char up = GameData::inputManager->ConvertToASCII(GameData::inputManager->getUpKey());
	char down = GameData::inputManager->ConvertToASCII(GameData::inputManager->getDownKey());
	char left = GameData::inputManager->ConvertToASCII(GameData::inputManager->getLeftKey());
	char right = GameData::inputManager->ConvertToASCII(GameData::inputManager->getRightKey());
	char jump = GameData::inputManager->ConvertToASCII(GameData::inputManager->getJumpKey());
	char pause = GameData::inputManager->ConvertToASCII(GameData::inputManager->getPauseKey());

	std::string UpString;
	UpString = up;
	UpString.append(" ");

	std::string DownString;
	DownString = down;
	DownString.append(" ");

	std::string LeftString;
	LeftString = left;
	LeftString.append(" ");

	std::string RightString;
	RightString = right;
	RightString.append(" ");

	std::string JumpString;
	JumpString = jump;
	JumpString.append(" ");

	std::string PauseString;
	PauseString = pause;
	PauseString.append(" ");

	Button* upBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", UpString);
	upBtn->setSize(new Vec2(50.0f, 50.0f));
	upBtn->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 230.0f));
	upBtn->setOrigin(new Vec2(0.0f, 0.0f));
	upBtn->setCallbackFunction([]() {
		//GameData::scene_manager->setCurrentScene("MainMenuScene", false);
		//GameData::inputManager->newUpKey();
	});
	Button* downBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", DownString);
	downBtn->setSize(new Vec2(50.0f, 50.0f));
	downBtn->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 280.0f));
	downBtn->setOrigin(new Vec2(0.0f, 0.0f));
	downBtn->setCallbackFunction([]() {
	//	GameData::inputManager->newDownKey();
	});
	Button* leftBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", LeftString);
	leftBtn->setSize(new Vec2(50.0f, 50.0f));
	leftBtn->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 350.0f));
	leftBtn->setOrigin(new Vec2(0.0f, 0.0f));
	leftBtn->setCallbackFunction([]() {
		//GameData::inputManager->newLeftKey();
	});
	Button* rightBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", RightString);
	rightBtn->setSize(new Vec2(50.0f, 50.0f));
	rightBtn->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 400.0f));
	rightBtn->setOrigin(new Vec2(0.0f, 0.0f));
	rightBtn->setCallbackFunction([]() {
		//GameData::inputManager->newRightKey();
	});
	Button* jmpBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", JumpString);
	jmpBtn->setSize(new Vec2(50.0f, 50.0f));
	jmpBtn->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 470.0f));
	jmpBtn->setOrigin(new Vec2(0.0f, 0.0f));
	jmpBtn->setCallbackFunction([]() {
		//GameData::inputManager->newJumpKey();
	});
	Button* pauseBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", PauseString);
	pauseBtn->setSize(new Vec2(50.0f, 50.0f));
	pauseBtn->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 520.0f));
	pauseBtn->setOrigin(new Vec2(0.0f, 0.0f));
	pauseBtn->setCallbackFunction([]() {
		//GameData::inputManager->newPauseKey();
	});

	go_list.push_back(upBtn);
	go_list.push_back(downBtn);
	go_list.push_back(leftBtn);
	go_list.push_back(rightBtn);
	go_list.push_back(jmpBtn);
	go_list.push_back(pauseBtn);
}

void OptionsMenu::volumeButtons()
{
	Button* MasterPlus = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "NULL");
	MasterPlus->setSize(new Vec2(50.0f, 50.0f));
	MasterPlus->setPosition(new Vec2(GameData::screen.Center().x - 330.0f, 520.0f));
	MasterPlus->setOrigin(new Vec2(0.0f, 0.0f));
	MasterPlus->setCallbackFunction([]() {
		//GameData::inputManager->newPauseKey();
	});
	Button* MasterMinus = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "NULL");
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
}