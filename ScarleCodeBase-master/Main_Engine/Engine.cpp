#include "Engine.h"
//C++
#include <windows.h>
#include <time.h>
#include <functional>

//DXTK

//Wrapper
#include "..\DXTK_Wrapper\Input_Manager.h"
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "Sprite.h"

//OURS
#include "GameObject.h"
#include "SceneManager.h"
#include "GameData.h"
#include "Platform.h"
#include "BaseCamera.h"
#include "LevelLoader.h"
#include "Game_Controller.h"
#include "Background.h"
#include "Collision_Manager.h"

#include "Scene.h"
#include "MainMenu.h"
#include "Object_Factory.h"


Engine::Engine(Renderer* _renderer, InputManager* _inputManager)
{
	GameData::inputManager = _inputManager;
	if (!GameData::inputManager->init())
	{
		OutputDebugString("Input manager failed to initialize");
	}
	GameData::renderer = _renderer;

	GameData::collsion_manager = new CollisionManager();;
	GameData::game_controller = new GameController();

	ObjectFactory::init();
	Platform::init();

	GameData::scene_manager = new SceneManager();
	GameData::scene_manager->addScene("MainMenuScene", new MainMenuScene());
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
	std::chrono::duration<float> elapsed_seconds = std::chrono::system_clock::now() - start;
	start = std::chrono::system_clock::now();

	GameData::scene_manager->getCurrentScene()->Update(elapsed_seconds.count());

	GameData::scene_manager->clearOldScenes();

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