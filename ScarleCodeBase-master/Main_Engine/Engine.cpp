#include "Engine.h"
//#ifdef __d3d11_1_h__
#include "DXTKRenderer.h"
#include "Input_Manager.h"
//#endif

//system headers
#include <windows.h>
#include <time.h>

#include "GameObjectV2.h"
#include "Sprite.h"
#include "PlayerV2.h"
#include "SceneManager.h"
#include "GameDataV2.h"

Engine::Engine(Renderer* _renderer, InputManager* _inputManager)
{
	//GameState::GS_MAIN_MENU;

	GameDataV2::inputManager = _inputManager;
	GameDataV2::renderer = _renderer;

}



Engine::~Engine()
{
	clearGameObjectList();

	delete GameDataV2::renderer;
	GameDataV2::renderer = nullptr;
	
	delete GameDataV2::inputManager;
	GameDataV2::inputManager = nullptr;
}



bool Engine::Update()
{
	/*auto iter = go_list.begin();
	for (; iter != go_list.end(); iter++)
	{
		(*iter)->Update();
	}*/

	//Just saying, a lot nicer syntax 
	for (auto go : go_list)
	{
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
	GameDataV2::renderer->BeginDraw();


	/*auto iter = go_list.begin();
	for (; iter != go_list.end(); iter++)
	{
		renderer->Draw(*iter);
	}*/

	//Just saying, a lot nicer syntax 
	for (const auto go : go_list)
	{
		GameDataV2::renderer->Draw(go);
	}

	GameDataV2::renderer->EndDraw();

	return true;
}

void Engine::clearGameObjectList()
{
	//Clears the go_list
	for (auto go : go_list)
	{
		delete go;
	}
	go_list.clear();
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