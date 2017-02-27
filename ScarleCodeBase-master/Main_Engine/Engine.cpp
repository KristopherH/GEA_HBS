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

	Sprite* ladder_spr = new Sprite("grass", GameDataV2::renderer);
	GameObjectV2* ladder = new GameObjectV2(ladder_spr, "Ladder", "Climable"); 
	ladder->SetSize(new Vec2(100.0f, 600.0f));
	ladder->SetPosition(new Vec2(50.0f, -100.0f));


	
	_GS = GameState::GS_MAIN_MENU;

<<<<<<< HEAD

		switch (_GS)
		{


		case GameState::GS_PLAY:

		{
=======
	player->SetPosition(new Vec2(0.0f, -800.0f));
	player->SetSize(new Vec2(100.0f, 150.0f));
	player->setGravity(true);

	player->setGravityTag("Slow Platform");
	player->setGravityTag("Sticky Platform");
	player->setGravityTag("Speed Platform");
	player->setGravityTag("Conveyor Platform");


	createPlatform.get()->slowPlatform(_renderer, -100.0f, -300.0f, 300.0f, 100.0f);

	createPlatform.get()->speedPlatform(_renderer, 200.0f, 0.0f, 300.0f, 100.0f);

	createPlatform.get()->stickyPlatform(_renderer, -400.0f, 0.0f, 300.0f, 100.0f);

	createPlatform.get()->conveyorPlatform(_renderer, -100.0f, 300.0f, 300.0f, 100.0f);

	GameDataV2::go_list.push_back(ladder);
	GameDataV2::go_list.push_back(createPlatform.get()->GetSlwPlat());
	GameDataV2::go_list.push_back(createPlatform.get()->GetSpdPlat());
	GameDataV2::go_list.push_back(createPlatform.get()->GetStkPlat());
	GameDataV2::go_list.push_back(createPlatform.get()->GetCnvyrPlat());
	GameDataV2::go_list.push_back(player);
>>>>>>> refs/remotes/origin/master

			initPlayGame();

<<<<<<< HEAD
			break;
		}
=======
	//Not essential but stops the risk of it interfering with the object that's in the vector
	player = nullptr;
	sprite1 = nullptr;
	ladder = nullptr;
	ladder_spr = nullptr;
>>>>>>> refs/remotes/origin/master

		case GameState::GS_MAIN_MENU:
		{
			//create a base camera
			BaseCamera* cam = new BaseCamera(GameDataV2::renderer->getWindowWidth(), GameDataV2::renderer->getWindowHeight(), -1.0f, 10000.0f);
			cam->SetPosition(new Vec2(0.0f, 0.0f));
			GameDataV2::go_list.push_back(cam);
			mainCamera = cam;

			Sprite* sprite2 = new Sprite("grass", GameDataV2::renderer);
			GameObjectV2* go2 = new GameObjectV2(sprite2, "Surface", "Surface");

			go2->SetPosition(new Vec2(10.0f, 100.0f));
			go2->SetSize(new Vec2(100.0f, 10.0f));

			GameDataV2::go_list.push_back(go2);

			if (!GameDataV2::inputManager->init())
			{
				OutputDebugString("Input manager failed to initialize");
			}

			go2 = nullptr;
			//break;

		}

		case GameState::GS_PAUSE:

		{
			break;
		}

		case GameState::GS_GAME_OVER:
		{



			break;
		}


		}
}

<<<<<<< HEAD



=======
>>>>>>> refs/remotes/origin/master
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
<<<<<<< HEAD
{

	for (auto go : GameDataV2::go_list)
	{
		go->gravityUpdate();
		go->Update();



	}
	Scene();
	return true;
}



bool Engine::Draw() 
{

	GameDataV2::renderer->BeginDraw(mainCamera);

	for (const auto go : GameDataV2::go_list)
=======
{	
	switch (_GS)
	{

	case GameState::GS_PLAY:
>>>>>>> refs/remotes/origin/master
	{
		GameDataV2::renderer->Draw(go);
	}

<<<<<<< HEAD
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
	GameDataV2::inputManager->readKeyboard();
		switch (_GS)
		{


		case GameState::GS_PLAY:

		{

			playGame();

			break;
		}

		case GameState::GS_MAIN_MENU:
		{
			
			if (GameDataV2::inputManager->getKeyDown('_'))
			{
				_GS = GameState::GS_PLAY;
				initPlayGame();
			}
			break;
		}
=======
	case GameState::GS_MAIN_MENU:
	{
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

		//double init of input manager
		/*if (!GameDataV2::inputManager->init())
		{
			OutputDebugString("Input manager failed to initialize");
		}*/
>>>>>>> refs/remotes/origin/master

		case GameState::GS_PAUSE:

<<<<<<< HEAD
=======
		/*if (GameDataV2::inputManager->getKeyHeld('_'))
>>>>>>> refs/remotes/origin/master
		{
			break;
		}

		case GameState::GS_GAME_OVER:
		{

<<<<<<< HEAD
			break;
		}
=======
		}*/
>>>>>>> refs/remotes/origin/master

		}
	

<<<<<<< HEAD
}
	


void Engine::createCollectible(float x , float y)
{

=======
	case GameState::GS_PAUSE:
	{
		break;
	}

	case GameState::GS_GAME_OVER:
	{	
		break;
	}
	}
	return true;
>>>>>>> refs/remotes/origin/master
}

void Engine::playGame()
{
<<<<<<< HEAD

=======
	GameDataV2::renderer->BeginDraw(mainCamera);
>>>>>>> refs/remotes/origin/master


}

void Engine::initPlayGame()
{
	Sprite* sprite1 = new Sprite("grass", GameDataV2::renderer);
	PlayerV2* go1 = new PlayerV2(sprite1, "Player", "Player");

<<<<<<< HEAD
	go1->SetPosition(new Vec2(0.0f, -200.0f));
	go1->SetSize(new Vec2(100.0f, 100.0f));
	go1->setGravity(true);
	go1->setGravityTag("Surface");
=======
void Engine::moveCamera(Vec2* _translation)
{
	mainCamera->movePosition(_translation);
}

>>>>>>> refs/remotes/origin/master

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

}