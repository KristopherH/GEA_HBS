#pragma once
//C++
#include <vector>
#include <memory>
#include <list>
//External


//Internal
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "GameDataV2.h"

#include <map> // remove after ttest

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
	//void createCollectible(Renderer * _renderer, InputManager * _inputManager);
	bool Draw(); // will pass an object at the renderer and ask to draw it
	void Scene();
	void clearGameObjectList();
	void playGame();
	float m_dt;
	void initPlayGame();
private:

 
protected:
	//GameDataV2* m_GD;
	std::map<char, std::function<void()>> KeyBindsPress;
	BaseCamera* mainCamera = nullptr;
 
};