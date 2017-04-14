#include "MainMenu.h"
#include "GameDataV2.h"
#include "Input_Manager.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "BaseCamera.h"
#include "LevelEditor.h"

MainMenuScene::MainMenuScene()
{
}

void MainMenuScene::Update(float dt)
{
	if (GameDataV2::inputManager->getKeyHeld(Inputs::USE) ||
		GameDataV2::inputManager->getMouseRight())
		{
			GameDataV2::scene_manager->addScene("GameScene", new GameScene());
			GameDataV2::scene_manager->setCurrentScene("GameScene", true);
		}
	if (GameDataV2::inputManager->getMouseLeft())
	{
		GameDataV2::scene_manager->addScene("Editor", new LevelEditorScene());
		GameDataV2::scene_manager->setCurrentScene("Editor", true);
	}
}

void MainMenuScene::Draw()
{
	GameDataV2::renderer->renderText("Build V1: Alpha\n\n\n\n\n\n   Press Enter", (cam->getPosition() + Vec2(150.0f, 200.0f)) * -1.0);
}
