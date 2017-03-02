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
#include "..\DXTK_Wrapper\Text.h"

#include "Platforms.h"
#include "BaseCamera.h"
#include <functional>

#include "LevelLoader.h"
#include "Game_Controller.h"

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
	createPlatform = std::make_unique<Platforms>();

	//create a base camera
	mainCamera = new BaseCamera(GameDataV2::renderer->getWindowWidth(), GameDataV2::renderer->getWindowHeight(), -1.0f, 10000.0f);
	//mainCamera->SetPosition(new Vec2(player->GetPosition().x + player->GetSize().x, player->GetPosition().y - player->GetSize().y));
	mainCamera->setName("Camera");
	mainCamera->setTag("Camera");
	GameDataV2::go_list.push_back(mainCamera);
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
		
		for (auto go : GameDataV2::go_list)
		{
			if (go->isAlive())
			{
				go->gravityUpdate();
				go->Update();
			}
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
		GameDataV2::inputManager->readKeyboard();

		if (GameDataV2::inputManager->getKeyHeld('_'))
		{
			_GS = GameState::GS_PLAY;
			playGame();
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
		if (go->isAlive())
			GameDataV2::renderer->Draw(go);
	}

	if (_GS == GameState::GS_MAIN_MENU)
	{
		GameDataV2::renderer->renderText("Build V1: Alpha\n\n\n\n\n\n   Press Space", (mainCamera->GetPosition() + Vec2(150.0f, 200.0f)) * -1.0);
	}

	if (_GS == GameState::GS_PLAY)
	{
		playerLives = std::to_string(player->getLives());
		GameDataV2::renderer->renderText("Lives: " + playerLives, (mainCamera->GetPosition() + Vec2(-600.0f, 550.0f)) * -1.0);
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


void Engine::playGame()
{
	Sprite* sprite1 = new Sprite("player_sprite", GameDataV2::renderer);
	player = new PlayerV2(sprite1, "Player", "Player");

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

	Level* level1 = LevelLoader::loadLevel("Level.txt");
	player->SetPosition(level1->playerStartingPosition);
	for (auto go : level1->go_list)
	{
		GameDataV2::go_list.push_back(go);
		go = nullptr;
	}

	int cam_location = GameDataV2::game_controller->getGameObjectLocation("Camera");
	if (cam_location >= 0)
	{
		BaseCamera* temp_cam = static_cast<BaseCamera*>(GameDataV2::go_list[cam_location]);
		temp_cam->setPlayerTracker(player);
		temp_cam = nullptr;
	}

	delete level1;	
}