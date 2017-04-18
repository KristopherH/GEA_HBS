#pragma once
//C++
#include <vector>
#include <memory>
#include <list>
#include <map>
#include <chrono>

//DXTK
#if defined _DXTK_
#include "../DXTK_Wrapper/Renderer.h"
#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/Renderer.h"
#endif

//OURS
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
	Engine(Renderer* _renderer, InputManager* _inputManager);

	~Engine();

	bool Update();
	bool Draw(); // will pass an object at the renderer and ask to draw it
	void moveCamera(Vec2* _translation);

protected: 
	BaseCamera* mainCamera = nullptr;
	BaseCamera* cam;

	std::chrono::time_point<std::chrono::system_clock> start;
};