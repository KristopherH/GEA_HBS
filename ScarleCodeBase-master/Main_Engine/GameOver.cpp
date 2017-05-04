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
#include "Button.h"
#include "Texture.h"
#include "DXTKRenderer.h"
#include "Sprite.h"
#include "CustomMath.h"
#include "GameFileCreation.h"
#include "Object_Factory.h"

GameOver::GameOver()
	:Scene()
{		
		GameObject* go = new GameObject(new Sprite("GameOverBackground", GameData::renderer));
		go->setSize(&GameData::currentCamera->getCameraSize());
		go->setPosition(&((GameData::currentCamera->getCameraSize()/2)*-1));
		go_list.push_back(go);

		Button* Playbtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "MainMenu");
		Playbtn->setSize(new Vec2(300.0f, 150.0f));
		Playbtn->setPosition(new Vec2(GameData::screen.Center().x - 300.0f, 700.0f));
		Playbtn->setOrigin(new Vec2(0.0f, 0.0f));
		Playbtn->setCallbackFunction([]() {
			GameData::scene_manager->setCurrentScene("MainMenuScene", false);
		});
		go_list.push_back(Playbtn);
}

void GameOver::Update(float dt)
{
	Scene::Update(dt);
}

void GameOver::Draw()
{
	Scene::Draw();

	GameData::renderer->renderText("Your Score: " + to_string(GameData::player->getScore()), Vec2(0.0f, 0.0f),
		Vec4(0.8f, 0.0f, 0.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
	std::vector<Sprite*> GameOver;

}


