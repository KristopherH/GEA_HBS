#include "Engine.h"
//C++
#include <windows.h>
#include <time.h>
#include <functional>

//DXTK

//Wrapper
#include "..\DXTK_Wrapper\Input_Manager.h"
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "..\DXTK_Wrapper\Sprite.h"
#include "..\DXTK_Wrapper\Text.h"

//OURS
#include "GameObjectV2.h"
#include "SceneManager.h"
#include "GameDataV2.h"
#include "Platforms.h"
#include "BaseCamera.h"
#include "LevelLoader.h"
#include "Game_Controller.h"
#include "Background.h"

#include "Scene.h"
#include "MainMenu.h"


Engine::Engine(Renderer* _renderer, InputManager* _inputManager,
				CollisionManager* _collision_manager, GameController* _game_controller)
{
	GameState::GS_MAIN_MENU;

	GameDataV2::inputManager = _inputManager;
	if (!GameDataV2::inputManager->init())
	{
		OutputDebugString("Input manager failed to initialize");
	}
	GameDataV2::renderer = _renderer;

	GameDataV2::collsion_manager = _collision_manager;
	GameDataV2::game_controller = _game_controller;
	createPlatform = std::make_unique<Platforms>(_renderer);

	GameDataV2::scene_manager = new SceneManager();
	GameDataV2::scene_manager->addScene("MainMenu", new MainMenuScene());
}

Engine::~Engine()
{
	mainCamera = nullptr;

	delete GameDataV2::renderer;
	GameDataV2::renderer = nullptr;

	delete GameDataV2::inputManager;
	GameDataV2::inputManager = nullptr;

	delete GameDataV2::collsion_manager;
	GameDataV2::collsion_manager = nullptr;

	delete GameDataV2::game_controller;
	GameDataV2::game_controller = nullptr;

	delete GameDataV2::scene_manager;
	GameDataV2::scene_manager = nullptr;
}

bool Engine::Update()
{	
	GameDataV2::scene_manager->getCurrentScene()->Update(0.0001f);

	return true;
}

bool Engine::Draw() 
{
	GameDataV2::renderer->BeginDraw(GameDataV2::scene_manager->getCurrentScene()->getCamera());

	GameDataV2::scene_manager->getCurrentScene()->Draw();
	
	GameDataV2::renderer->EndDraw();

	return true;
}

void Engine::moveCamera(Vec2* _translation)
{
	mainCamera->movePosition(_translation);
}