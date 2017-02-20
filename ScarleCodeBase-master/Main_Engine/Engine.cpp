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
	
	Sprite* sprite1 = new Sprite("grass", renderer);
	GameObjectV2* go1 = new GameObjectV2(sprite1);
	go1->SetPosition(new Vec2(10.0f, 10.0f));
	go1->SetSize(new Vec2(0.5f, 0.5f));
	go_list.push_back(go1);
}

Engine::~Engine()
{
}

bool Engine::Update()
{
	auto iter = go_list.begin();
	for (; iter != go_list.end(); iter++)
	{
		(*iter)->Update();
	}

	return true;
}

bool Engine::Draw() 
{
	renderer->BeginDraw();

	auto iter = go_list.begin();
	for (; iter != go_list.end(); iter++)
	{
		renderer->Draw(*iter);
	}

	renderer->EndDraw();

	return  true;
}
