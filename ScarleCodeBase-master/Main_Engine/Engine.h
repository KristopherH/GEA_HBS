#pragma once
//C++
#include <vector>
#include <memory>

//External


//Internal

//Definitions
class GameObjectV2;
class Renderer; //Find a way of loading the right renderer based on what engine is loaded
class InputManager;

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

	Renderer* renderer;
	InputManager* inputManager;
};