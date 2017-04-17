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
#include "GameObject.h"
#include "SceneManager.h"
#include "GameData.h"
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

	GameData::inputManager = _inputManager;
	if (!GameData::inputManager->init())
	{
		OutputDebugString("Input manager failed to initialize");
	}
	GameData::renderer = _renderer;

	GameData::collsion_manager = _collision_manager;
	GameData::game_controller = _game_controller;
	createPlatform = std::make_unique<Platforms>(_renderer);

	GameData::scene_manager = new SceneManager();
	GameData::scene_manager->addScene("MainMenu", new MainMenuScene());
}

Engine::~Engine()
{
	mainCamera = nullptr;

	delete GameData::renderer;
	GameData::renderer = nullptr;

	delete GameData::inputManager;
	GameData::inputManager = nullptr;

	delete GameData::collsion_manager;
	GameData::collsion_manager = nullptr;

	delete GameData::game_controller;
	GameData::game_controller = nullptr;

	delete GameData::scene_manager;
	GameData::scene_manager = nullptr;
}

bool Engine::Update()
{	
	GameData::scene_manager->getCurrentScene()->Update(0.0001f);

	return true;
}

bool Engine::Draw() 
{
	GameData::renderer->BeginDraw(GameData::scene_manager->getCurrentScene()->getCamera());

	GameData::scene_manager->getCurrentScene()->Draw();
	
	GameData::renderer->EndDraw();

	return true;
}

void Engine::moveCamera(Vec2* _translation)
{
	mainCamera->movePosition(_translation);
}