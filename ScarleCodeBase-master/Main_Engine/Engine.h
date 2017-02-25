#pragma once
//C++
#include <vector>
#include <memory>

//External

//Internal
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "GameDataV2.h"
#include "../DXTK_Wrapper/Text.h"

//Definitions
class GameObjectV2;

class Engine
{
public:
	Engine(Renderer* _renderer, InputManager* _inputManager, 
			CollisionManager* _collision_manager, GameController* _game_controller);
	~Engine();

	bool Update();
	void createCollectible(float x, float y);
	bool Draw(); // will pass an object at the renderer and ask to draw it

	void clearGameObjectList();

private:

	BaseCamera* mainCamera = nullptr;
};