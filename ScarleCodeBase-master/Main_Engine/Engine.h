#pragma once
//C++
#include <vector>
#include <memory>
#include <list>
//External

//Internal
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "GameDataV2.h"
#include "../DXTK_Wrapper/Text.h"

using std::list;
using std::unique_ptr;

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
	void Scene();
	void clearGameObjectList();

	float m_dt;

private:

 
protected:
	//GameDataV2* m_GD;
 
	BaseCamera* mainCamera = nullptr;
 
};