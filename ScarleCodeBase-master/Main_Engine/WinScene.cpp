#include "WinScene.h"
#include "Text.h"
#include "Button.h"
#include <string>
#include "Object_Factory.h"
#include "SceneManager.h"
#include "MainMenu.h"

WinScene::WinScene(float _timeTaken)
	:timeTaken(_timeTaken), Scene()
{

	GameObject* background = new GameObject(new Sprite("11_background", GameData::renderer));
	background->setSize(new Vec2(GameData::currentCamera->getViewSize().x, 
								 GameData::currentCamera->getViewSize().x));
	background->setPosition(new Vec2(-GameData::currentCamera->getViewSize().x / 2,
									 -GameData::currentCamera->getViewSize().y / 2));
	go_list.push_back(background);


	Text* txt = new Text(nullptr, "txt", "NULL", "You Won\n what an achievement...");
	txt->setSize(new Vec2(GameData::currentCamera->getViewSize().x, 100));
	txt->setPosition(new Vec2(GameData::currentCamera->getViewSize().x / 2 - (txt->getSize().x / 2),
							  0.0f));
	go_list.push_back(txt);

	Text* txt2 = new Text(nullptr, "txt", "NULL", "Time: " + to_string(timeTaken));
	txt2->setSize(new Vec2(GameData::currentCamera->getViewSize().x, 50));
	txt2->setPosition(new Vec2(GameData::currentCamera->getViewSize().x / 2 - (txt2->getSize().x / 2),
								GameData::currentCamera->getViewSize().y / 2 + (txt2->getSize().y)));
	go_list.push_back(txt2);

	Vec2 pos;
	Vec2 btnSize;
	btnSize += Vec2(300, 100);

	Button* btn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]), "MainMenu", "NULL", "Main Menu");
	go_list.push_back(btn);
	btn->setSize(&btnSize);
	pos += Vec2(GameData::currentCamera->getViewSize().x / 2 - (btn->getSize().x / 2),
				GameData::currentCamera->getViewSize().y / 2 + (btn->getSize().y));
	btn->setPosition(&pos);
	btn->setCallbackFunction([](){
		GameData::scene_manager->addScene("MainMenu", new MainMenuScene());
		GameData::scene_manager->setCurrentScene("MainMenu");
		return;
	});

	pos.y += btnSize.y;
	Button* btn1 = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]), "MainMenu", "NULL", "Quit");
	go_list.push_back(btn1);
	btn1->setSize(&btnSize);
	btn1->setPosition(&pos);
	btn1->setCallbackFunction([]() {
		exit(0);
		return;
	});


}

WinScene::~WinScene()
{

}
