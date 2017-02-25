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
<<<<<<< HEAD
#include "SceneManager.h"
#include "GameDataV2.h"
=======
#include "BaseCamera.h"
#include "GameDataV2.h"

>>>>>>> refs/remotes/origin/master

Engine::Engine(Renderer* _renderer, InputManager* _inputManager,
				CollisionManager* _collision_manager, GameController* _game_controller)
{
	//GameState::GS_MAIN_MENU;

	GameDataV2::inputManager = _inputManager;
	GameDataV2::renderer = _renderer;
<<<<<<< HEAD

=======
	GameDataV2::collsion_manager = _collision_manager;
	GameDataV2::game_controller = _game_controller;

	Sprite* sprite1 = new Sprite("grass", GameDataV2::renderer);
	PlayerV2* go1 = new PlayerV2(sprite1, "Player", "Player");

	go1->SetPosition(new Vec2(0.0f, -800.0f));
	go1->SetSize(new Vec2(100.0f, 100.0f));
	go1->setGravity(true);
	go1->setGravityTag("Surface");

	Sprite* sprite2 = new Sprite("grass", GameDataV2::renderer);
	GameObjectV2* go2 = new GameObjectV2(sprite2, "Surface", "Surface");

	go2->SetPosition(new Vec2(10.0f, 100.0f));
	go2->SetSize(new Vec2(100.0f, 10.0f));

	GameDataV2::go_list.push_back(go1);
	GameDataV2::go_list.push_back(go2);

	//create a base camera
	BaseCamera* cam = new BaseCamera(GameDataV2::renderer->getWindowWidth(), GameDataV2::renderer->getWindowHeight(), -1.0f, 10000.0f);
	cam->SetPosition(new Vec2(0.0f, 0.0f));
	GameDataV2::go_list.push_back(cam);
	mainCamera = cam;

	//Not essential but stops the risk of it interfering with the object that's in the vector
	go1 = nullptr;
	go2 = nullptr;
	sprite1 = nullptr;

	//double init of input manager
	if (!GameDataV2::inputManager->init())
	{
		OutputDebugString("Input manager failed to initialize");
	}
>>>>>>> refs/remotes/origin/master
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
	for (auto go : GameDataV2::go_list)
	{
		go->gravityUpdate();
		go->Update();
	}


	switch (_GS)
	{


	case GameState::GS_PLAY:

	{
		break;
	}

	case GameState::GS_MAIN_MENU:
	{


		Sprite* sprite1 = new Sprite("grass", GameDataV2::renderer);
		PlayerV2* go1 = new PlayerV2(sprite1);

		go1->SetPosition(new Vec2(10.0f, 10.0f));
		go1->SetSize(new Vec2(0.5f, 0.5f));
		go_list.push_back(go1);

		//Not essential but stops the risk of it interfering with the object that's in the vector
		go1 = nullptr;
		sprite1 = nullptr;

		if (!GameDataV2::inputManager->init())
		{
			OutputDebugString("Input manager failed to initialize");
		}



		if (GameDataV2::inputManager->getKeyHeld('_'))
		{

			_GS = GameState::GS_GAME_OVER;

		}

	}

	case GameState::GS_PAUSE:

	{
		break;
	}

	case GameState::GS_GAME_OVER:
	{
		/*
		GameDataV2::inputManager = _inputManager;
		GameDataV2::renderer = _renderer;
		Sprite* gameOver = new Sprite("white", GameDataV2::renderer);

		PlayerV2* go1 = new PlayerV2(gameOver);

		go1->SetPosition(new Vec2(10.0f, 10.0f));
		go1->SetSize(new Vec2(0.5f, 0.5f));
		go_list.push_back(go1);

		*/
		break;
	}
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