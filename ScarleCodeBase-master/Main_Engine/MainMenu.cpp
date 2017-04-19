#include "MainMenu.h"
//C++

//DXTK
#if defined _DXTK_
#include "..\DXTK_Wrapper\CustomMath.h"
#include "..\DXTK_Wrapper\Renderer.h"
#include "../DXTK_Wrapper/Texture.h"
#include "../DXTK_Wrapper/InputManager.h"
#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/CustomMath.h"
#include "../Phyre/Code/Texture.h"
#include "../Phyre/Code/Renderer.h"
#include "../Phyre/Code/InputManager.h"
#endif

//OURS
#include "GameData.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "BaseCamera.h"
#include "LevelEditor.h"
#include "Button.h"
#include "Sprite.h"


MainMenuScene::MainMenuScene()
{
	Scene::Scene();
	Button* btn = new Button(new Sprite("Button", GameData::renderer), "button1", "");
	btn->setSize(new Vec2(200.0f, 100.0f));
	btn->setPosition(new Vec2(0.0f, 0.0f)/*&GameData::screen.Center()*/);
	btn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("GameScene", new GameScene());
		GameData::scene_manager->setCurrentScene("GameScene");
	});
	go_list.push_back(btn);
	Button* btn1 = new Button(new Sprite("Button", GameData::renderer), "button1", "");
	btn1->setSize(new Vec2(200.0f, 100.0f));
	btn1->setPosition(new Vec2(GameData::screen.Center().x - btn1->getSize().x/2, 400.0f)/*&GameData::screen.Center()*/);
	btn1->setCallbackFunction([]() {
		GameData::scene_manager->addScene("LevelEditorScene", new LevelEditorScene());
		GameData::scene_manager->setCurrentScene("LevelEditorScene");
	});
	go_list.push_back(btn1);
}

void MainMenuScene::Update(float dt)
{
	//if (GameData::inputManager->getKeyHeld(Inputs::USE) ||
	//	GameData::inputManager->getMouseLeft())
	//	{
	//		GameData::scene_manager->addScene("GameScene", new GameScene());
	//		GameData::scene_manager->setCurrentScene("GameScene", true);
	//	}
	//if (GameData::inputManager->getMouseRight())
	//{
	//	GameData::scene_manager->addScene("Editor", new LevelEditorScene());
	//	GameData::scene_manager->setCurrentScene("Editor", true);
	//}
	Scene::Update(dt);
}

void MainMenuScene::Draw()
{
	//GameData::renderer->renderText("Build V1: Alpha\n\n\n\n\n\n   Press Enter", (cam->getPosition() + Vec2(150.0f, 200.0f)) * -1.0);
	Scene::Draw();
}
