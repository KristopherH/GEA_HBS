#pragma once
//C++
#include <vector>
#include <memory>

//External


//Internal
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "GameDataV2.h"

//Definitions
class GameObjectV2;

class Engine
{
public:
	Engine(Renderer* _renderer, InputManager* _inputManager);
	~Engine();

	bool Update();
	bool Draw(); // will pass an object at the renderer and ask to draw it

	void clearGameObjectList();

private:
	std::vector<GameObjectV2*> go_list;

};