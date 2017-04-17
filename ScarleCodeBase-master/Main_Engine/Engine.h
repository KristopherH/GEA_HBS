#pragma once
//C++
#include <vector>
#include <memory>
#include <list>
#include <map>
#include <chrono>

//DXTK

//OURS
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "GameData.h"

using std::list;
using std::unique_ptr;

//Definitions
class GameObject;
class Platforms;
class Text;
class Player;

class Engine
{
public:
	Engine(Renderer* _renderer, InputManager* _inputManager, 
			CollisionManager* _collision_manager, GameController* _game_controller);

	~Engine();

	bool Update();
	bool Draw(); // will pass an object at the renderer and ask to draw it
	void moveCamera(Vec2* _translation);

protected: 
	BaseCamera* mainCamera = nullptr;
	BaseCamera* cam;

	std::chrono::time_point<std::chrono::system_clock> start;
};