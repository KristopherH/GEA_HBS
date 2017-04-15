#include "MainMenu.h"
#include "GameDataV2.h"
#include "Input_Manager.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "BaseCamera.h"
#include "LevelEditor.h"
#include "Button.h"
#include "Texture.h"
#include "DXTKRenderer.h"
#include "Sprite.h"
#include "CustomMath.h"

MainMenuScene::MainMenuScene()
{
	Scene::Scene();
	Button* btn = new Button(new Sprite("Button", GameDataV2::renderer), "button1", "");
	btn->setSize(new Vec2(600.0f, 300.0f));
	btn->setPosition(new Vec2(0.0f, 0.0f)/*&GameDataV2::screen.Center()*/);
	btn->setCallbackFunction([]() {
		GameDataV2::scene_manager->addScene("GameScene", new GameScene());
		GameDataV2::scene_manager->setCurrentScene("GameScene");
	});
	go_list.push_back(btn);
}

void MainMenuScene::Update(float dt)
{
	//if (GameDataV2::inputManager->getKeyHeld(Inputs::USE) ||
	//	GameDataV2::inputManager->getMouseLeft())
	//	{
	//		GameDataV2::scene_manager->addScene("GameScene", new GameScene());
	//		GameDataV2::scene_manager->setCurrentScene("GameScene", true);
	//	}
	//if (GameDataV2::inputManager->getMouseRight())
	//{
	//	GameDataV2::scene_manager->addScene("Editor", new LevelEditorScene());
	//	GameDataV2::scene_manager->setCurrentScene("Editor", true);
	//}
	Scene::Update(dt);
}

void MainMenuScene::Draw()
{
	GameDataV2::renderer->renderText("Build V1: Alpha\n\n\n\n\n\n   Press Enter", (cam->getPosition() + Vec2(150.0f, 200.0f)) * -1.0);
	Scene::Draw();
}
