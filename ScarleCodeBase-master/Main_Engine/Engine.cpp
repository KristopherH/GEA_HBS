#include "Engine.h"
//#ifdef __d3d11_1_h__
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "..\DXTK_Wrapper\Input_Manager.h"
//#endif

//system headers
#include <windows.h>
#include <time.h>

#include "GameObjectV2.h"
#include "..\DXTK_Wrapper\Sprite.h"
#include "PlayerV2.h"
#include "SceneManager.h"
#include "GameDataV2.h"

#include "Platforms.h"
#include "BaseCamera.h"
#include <functional>

Engine::Engine(Renderer* _renderer, InputManager* _inputManager,
				CollisionManager* _collision_manager, GameController* _game_controller)
{
	//GameState::GS_MAIN_MENU

	GameDataV2::inputManager = _inputManager;
	GameDataV2::renderer = _renderer;

	GameDataV2::collsion_manager = _collision_manager;
	GameDataV2::game_controller = _game_controller;
	createPlatform = std::make_unique<Platforms>();

	Sprite* sprite1 = new Sprite("player_sprite", GameDataV2::renderer);
	PlayerV2* player = new PlayerV2(sprite1, "Player", "Player");

	Sprite* ladder_spr = new Sprite("Ladder", GameDataV2::renderer);
	GameObjectV2* ladder = new GameObjectV2(ladder_spr, "Ladder", "Climable"); 
	ladder->SetSize(new Vec2(100.0f, 300.0f));
	ladder->SetPosition(new Vec2(600.0f, 250.0f));
	ladder->setSolid(false);

	_GS = GameState::GS_MAIN_MENU;

	player->SetPosition(new Vec2(-800.0f, 200.0f));
	player->SetSize(new Vec2(100.0f, 150.0f));
	player->setGravity(true);

	player->setGravityTag("Slow Platform");
	player->setGravityTag("Sticky Platform");
	player->setGravityTag("Speed Platform");
	player->setGravityTag("Conveyor Platform");
	player->setGravityTag("Jump Platform");
	player->setGravityTag("Standard Platform");
	
	GameDataV2::go_list.push_back(ladder);
	GameDataV2::go_list.push_back(createPlatform.get()->standardPlatform(_renderer, -800.0f, 500.0f, 1600.0f, 100.0f));
	GameDataV2::go_list.push_back(createPlatform.get()->slowPlatform(_renderer, 400.0f, -300.0f, 300.0f, 100.0f));
	//GameDataV2::go_list.push_back(createPlatform.get()->jumpPlatform(_renderer, -100.0f, -300.0f, 300.0f, 100.0f));
	GameDataV2::go_list.push_back(createPlatform.get()->speedPlatform(_renderer, 200.0f, 0.0f, 300.0f, 100.0f));
	GameDataV2::go_list.push_back(createPlatform.get()->stickyPlatform(_renderer, -400.0f, 0.0f, 300.0f, 100.0f));
	GameDataV2::go_list.push_back(createPlatform.get()->conveyorPlatform(_renderer, 500.0f, 200.0f, 300.0f, 100.0f, true));
	GameDataV2::go_list.push_back(player);

	//create a base camera
	BaseCamera* cam = new BaseCamera(GameDataV2::renderer->getWindowWidth(), GameDataV2::renderer->getWindowHeight(), -1.0f, 10000.0f);
	cam->SetPosition(new Vec2(0.0f, 0.0f));
	cam->setName("Camera");
	cam->setTag("Camera");
	GameDataV2::go_list.push_back(cam);
	mainCamera = cam;

	//Not essential but stops the risk of it interfering with the object that's in the vector
	player = nullptr;
	sprite1 = nullptr;
	ladder = nullptr;
	ladder_spr = nullptr;

	//double init of input manager
	if (!GameDataV2::inputManager->init())
	{
		OutputDebugString("Input manager failed to initialize");
	}
}

Engine::~Engine()
{
	clearGameObjectList();

	mainCamera = nullptr;

	delete GameDataV2::renderer;
	GameDataV2::renderer = nullptr;

	delete GameDataV2::inputManager;
	GameDataV2::inputManager = nullptr;

	delete GameDataV2::collsion_manager;
	GameDataV2::collsion_manager = nullptr;

	delete GameDataV2::game_controller;
	GameDataV2::game_controller = nullptr;
}

bool Engine::Update()
{	
	switch (_GS)
	{

	case GameState::GS_PLAY:
		break;

	case GameState::GS_MAIN_MENU:
		for (auto go : GameDataV2::go_list)
		{
			go->gravityUpdate();
			go->Update();
		}

		if (GameDataV2::inputManager->getKeyHeld('8'))
		{
			moveCamera(new Vec2(0.0f, 1.0f));
		}
		if (GameDataV2::inputManager->getKeyHeld('4'))
		{
			moveCamera(new Vec2(1.0f, 0.0f));
		}
		if (GameDataV2::inputManager->getKeyHeld('2'))
		{
			moveCamera(new Vec2(0.0f, -1.0f));
		}
		if (GameDataV2::inputManager->getKeyHeld('6'))
		{
			moveCamera(new Vec2(-1.0f, 0.0f));
		}

	case GameState::GS_PAUSE:
		break;

	case GameState::GS_GAME_OVER:
		break;

	default:
		break;
	}
	return true;
}



bool Engine::Draw() 
{
	GameDataV2::renderer->BeginDraw(mainCamera);

	for (const auto go : GameDataV2::go_list)
	{
		GameDataV2::renderer->Draw(go);
	}

	GameDataV2::renderer->EndDraw();

	return true;
}

void Engine::clearGameObjectList()
{
	//Clears the go_list
	for (auto go : GameDataV2::go_list)
	{
		delete go;
	}
	GameDataV2::go_list.clear();
}

void Engine::moveCamera(Vec2* _translation)
{
	mainCamera->movePosition(_translation);
}


void Engine::Scene()
{
	/*
	DWORD currentTime = GetTickCount();
	m_GD->m_dt = min((float)(currentTime - m_playTime) / 1000.0f, 0.1f);
	m_playTime = currentTime;
	

	if (GameState::GS_PLAY)
	{

	}

	if (GameState::GS_MAIN_MENU)
	{

	}

	if (GameState::GS_PAUSE)
	{

	}

	if (GameState::GS_GAME_OVER)
	{

	}
*/
}