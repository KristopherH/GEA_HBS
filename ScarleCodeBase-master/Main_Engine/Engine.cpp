#include "Engine.h"
//#ifdef __d3d11_1_h__
#include "..\DXTK_Wrapper\DXTKRenderer.h"
#include "..\DXTK_Wrapper\Input_Manager.h"
#include "../Game/Helper.h"
//#endif

//system headers
#include <windows.h>
#include <time.h>

#include "GameObjectV2.h"
#include "..\DXTK_Wrapper\Sprite.h"
#include "PlayerV2.h"
#include "SceneManager.h"
#include "GameDataV2.h"
#include "..\DXTK_Wrapper\Text.h"

#include "Platforms.h"
#include "BaseCamera.h"
#include <functional>

#include "LevelLoader.h"

Engine::Engine(Renderer* _renderer, InputManager* _inputManager,
				CollisionManager* _collision_manager, GameController* _game_controller)
{
	//GameState::GS_MAIN_MENU

	GameDataV2::inputManager = _inputManager;
	GameDataV2::renderer = _renderer;

	GameDataV2::collsion_manager = _collision_manager;
	GameDataV2::game_controller = _game_controller;
	createPlatform = std::make_unique<Platforms>();
	//createText = std::make_unique<Text>();

	Sprite* sprite1 = new Sprite("player_sprite", GameDataV2::renderer);
	player = new PlayerV2(sprite1, "Player", "Player");


	_GS = GameState::GS_MAIN_MENU;

	player->SetPosition(new Vec2(-475.0f, 350.0f));
	player->SetSize(new Vec2(100.0f, 120.0f));
	player->setGravity(true);

	player->setGravityTag("Slow Platform");
	player->setGravityTag("Sticky Platform");
	player->setGravityTag("Speed Platform");
	player->setGravityTag("Conveyor Platform");
	player->setGravityTag("Jump Platform");
	player->setGravityTag("Standard Platform");
	

	GameDataV2::go_list.push_back(player);

	

	//first level of platforms

	//GameDataV2::go_list.push_back(createLadder(-475.0f, -300.0f, 100.0f, 550.0f, false, "ladder1"));
	//GameDataV2::go_list.push_back(createLadder(600.0f, 175.0f, 100.0f, 350.0f, false, "ladder2"));
	
	//GameDataV2::go_list.push_back(createPlatform.get()->standardPlatform(_renderer, -800.0f, 500.0f, 1600.0f, 100.0f, "standard1"));
	//GameDataV2::go_list.push_back(createPlatform.get()->speedPlatform(_renderer, -200.0f, 200.0f, 700.0f, 100.0f, "speed"));
	//GameDataV2::go_list.push_back(createPlatform.get()->conveyorPlatform(_renderer, "Conveyor Left", 500.0f, 100.0f, 300.0f, 100.0f, true));
	
	//first level of platforms
	//GameDataV2::go_list.push_back(createPlatform.get()->slowPlatform(_renderer, -500.0f, 200.0f, 300.0f, 100.0f, "slow"));
	//GameDataV2::go_list.push_back(createPlatform.get()->stickyPlatform(_renderer, -100.0f, -350.0f, 300.0f, 100.0f, "sticky"));
	//GameDataV2::go_list.push_back(createCollectible(-455.0f, -570.0f, 50.0f, 50.0f));
	//GameDataV2::go_list.push_back(createPlatform.get()->conveyorPlatform(_renderer, "Conveyor Right", -300.0f, -250.0f, 200.0f, 100.0f, false));
	//GameDataV2::go_list.push_back(createPlatform.get()->conveyorPlatform(_renderer, "Conveyor Left", -100.0f, -150.0f, 200.0f, 100.0f, false));
	//GameDataV2::go_list.push_back(createPlatform.get()->speedPlatform(_renderer, 100.0f, -150.0f, 300.0f, 100.0f, "speed2"));
	//GameDataV2::go_list.push_back(createPlatform.get()->standardPlatform(_renderer, -100.0f, -150.0f, 200.0f, 100.0f, "standard3"));
	//GameDataV2::go_list.push_back(createPlatform.get()->jumpPlatform(_renderer, 400.0f, -150.0f, 200.0f, 100.0f, "jump"));
	//GameDataV2::go_list.push_back(createPlatform.get()->standardPlatform(_renderer, 650.0f, -150.0f, 100.0f, 100.0f, "standard2"));
	//GameDataV2::go_list.push_back(createCollectible(665.0f, -250.0f, 50.0f, 50.0f));

	

	Level* level1 = LevelLoader::loadLevel("Level.txt");
	//player->SetPosition(&level1->playerStartingPosition);
	for (auto go : level1->go_list)
	{
		GameDataV2::go_list.push_back(go);
		go = nullptr;
	}
	//delete level1;

	//createText.get()->createString("Hi", GameDataV2::renderer);
	
	//GameDataV2::go_list.push_back(_renderer->DrawString(Helper::charToWChar("Hi"),Vec2(0.0f,0.0f), Vec4(0.0f,0.0f,0.0f,0.0f), 0.0f, Vec2(0.0f, 0.0f),0.0f, 2.0f));

	//create a base camera
	cam = new BaseCamera(GameDataV2::renderer->getWindowWidth(), GameDataV2::renderer->getWindowHeight(), -1.0f, 10000.0f);
	cam->SetPosition(new Vec2(0.0f, 0.0f));
	cam->setName("Camera");
	cam->setTag("Camera");
	GameDataV2::go_list.push_back(cam);
	mainCamera = cam;

	//Not essential but stops the risk of it interfering with the object that's in the vector
	//player = nullptr;
	sprite1 = nullptr;

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

	GameDataV2::renderer->renderText("Lives: 3", cam->GetPosition()*-1.0);

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

GameObjectV2* Engine::createLadder(float x, float y, float sizeX, float sizeY, bool solid, string name)
{
	ladder_spr = nullptr;
	ladder = nullptr;

	ladder_spr = new Sprite("Ladder", GameDataV2::renderer);
	ladder = new GameObjectV2(ladder_spr, name, "Climbable");

	ladder->SetPosition(new Vec2(x, y));
	ladder->SetSize(new Vec2(sizeX, sizeY));
	ladder->setSolid(solid);

	
	return ladder;
}

GameObjectV2 * Engine::createCollectible(float x, float y, float sizeX, float sizeY)
{
	collectible_spr = nullptr;
	collectible = nullptr;

	collectible_spr = new Sprite("coin", GameDataV2::renderer);
	collectible = new GameObjectV2(collectible_spr, "Collectible", "Collectible");

	collectible->SetPosition(new Vec2(x, y));
	collectible->SetSize(new Vec2(sizeX, sizeY));

	return collectible;
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