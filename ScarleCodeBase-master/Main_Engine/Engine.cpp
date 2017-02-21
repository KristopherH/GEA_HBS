#include "Engine.h"
//#ifdef __d3d11_1_h__
#include "DXTKRenderer.h"
#include "Input_Manager.h"
//#endif

#include "GameObjectV2.h"
#include "Sprite.h"


Engine::Engine(Renderer* _renderer, InputManager* _inputManager)
	:renderer(_renderer), inputManager(_inputManager)
{
	////Not essential but stops the risk of it interfering with the object that's in the vector
	//go1 = nullptr;
	//sprite1 = nullptr;
	createCollectible(300, 300);

	if (!inputManager->init())
	{
		OutputDebugString("Input manager failed to initialize");
	}
}

Engine::~Engine()
{
	clearGameObjectList();

	delete renderer;
	renderer = nullptr; 
	
	delete inputManager;
	inputManager = nullptr;
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

void Engine::createCollectible(float x, float y)
{
	// create coin collectible
	Sprite* collectible = new Sprite("coin", renderer);
	GameObjectV2* ctbl = new GameObjectV2(collectible, inputManager);
	ctbl->SetSize(new Vec2(0.15f, 0.15f));

	// pass in custom position
	ctbl->SetPosition(new Vec2(x, y));

	go_list.push_back(ctbl);
}

bool Engine::Draw() 
{
	renderer->BeginDraw();


	/*auto iter = go_list.begin();
	for (; iter != go_list.end(); iter++)
	{
		renderer->Draw(*iter);
	}*/

	//Just saying, a lot nicer syntax 
	for (const auto go : go_list)
	{
		renderer->Draw(go);
	}

	renderer->EndDraw();

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
