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
#include "PlayerV2.h"
#include "SceneManager.h"
#include "GameDataV2.h"
#include "Platforms.h"
#include "BaseCamera.h"
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
	createPlatform = std::make_unique<Platforms>(_renderer);

	//create a base camera
	mainCamera = new BaseCamera(GameDataV2::renderer->getWindowWidth(), GameDataV2::renderer->getWindowHeight(), -1.0f, 10000.0f);
	//mainCamera->SetPosition(new Vec2(player->GetPosition().x + player->GetSize().x, player->GetPosition().y - player->GetSize().y));
	mainCamera->setName("Camera");
	mainCamera->setTag("Camera");
	mainCamera->setSolid(false);
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
			if (go->getAlive())
			{
				go->gravityUpdate();
				go->Update();
			}
		}
		lives = player->getLives();
		break;

	case GameState::GS_MAIN_MENU:
		if (GameDataV2::inputManager->getKeyHeld(Inputs::USE) ||
			GameDataV2::inputManager->getMouseRight())
		{
			_GS = GameState::GS_PLAY;
			playGame();
		}
		break;

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
		if (go->getAlive())
			GameDataV2::renderer->Draw(go);
	}

	if (_GS == GameState::GS_MAIN_MENU)
	{
		GameDataV2::renderer->renderText("Build V1: Alpha\n\n\n\n\n\n   Press Enter", (mainCamera->getPosition() + Vec2(150.0f, 200.0f)) * -1.0);
	}

	if (_GS == GameState::GS_PLAY)
	{
		GameDataV2::renderer->renderText("Lives: " + std::to_string(lives), (mainCamera->getPosition() + Vec2(-600.0f, 450.0f)) * -1.0);
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

	ladder->setPosition(new Vec2(x, y));
	ladder->setSize(new Vec2(sizeX, sizeY));
	ladder->setSolid(solid);

	
	return ladder;
}

GameObjectV2 * Engine::createCollectible(float x, float y, float sizeX, float sizeY)
{
	collectible_spr = nullptr;
	collectible = nullptr;

	collectible_spr = new Sprite("coin", GameDataV2::renderer);
	collectible = new GameObjectV2(collectible_spr, "Collectible", "Collectible");

	collectible->setPosition(new Vec2(x, y));
	collectible->setSize(new Vec2(sizeX, sizeY));

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

	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(new Vec2(-475.0f, 350.0f));
	player->setGravity(true);

	player->setGravityTag("Slow Platform");
	player->setGravityTag("Sticky Platform");
	player->setGravityTag("Speed Platform");
	player->setGravityTag("Conveyor Left");
	player->setGravityTag("Conveyor Right");
	player->setGravityTag("Jump Platform");
	player->setGravityTag("Standard Platform");

	GameDataV2::go_list.push_back(player);

	Level* level1 = LevelLoader::loadLevel("Level.txt");
	player->setPosition(level1->playerStartingPosition);
	for (auto go : level1->go_list)
	{
		GameDataV2::go_list.push_back(go);
		go = nullptr;
	}
	delete level1;

	int cam_location = GameDataV2::game_controller->getGameObjectLocation("Camera");
	if (cam_location >= 0)
	{
		BaseCamera* temp_cam = static_cast<BaseCamera*>(GameDataV2::go_list[cam_location]);
		temp_cam->setPlayerTracker(player);
		temp_cam = nullptr;
	}
	
}