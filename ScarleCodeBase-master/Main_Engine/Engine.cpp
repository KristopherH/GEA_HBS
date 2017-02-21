#include "Engine.h"
//#ifdef __d3d11_1_h__
#include "DXTKRenderer.h"
#include "Input_Manager.h"
//#endif

#include "GameObjectV2.h"
#include "Sprite.h"
#include "PlayerV2.h"


Engine::Engine(Renderer* _renderer, InputManager* _inputManager)
{
	GameDataV2::inputManager = _inputManager;
	GameDataV2::renderer = _renderer;
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
