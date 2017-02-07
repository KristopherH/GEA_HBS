#pragma once
//C++
#include <vector>
#include <memory>

//External


//Internal

//Definitions
class GameObject;
class Renderer; //Find a way of loading the right renderer based on what engine is loaded

class Engine
{
public:
	Engine();
	~Engine();

	bool Update();
	bool Draw(); // will pass an object at the renderer and ask to draw it

private:
	std::vector<GameObject*> go_list;

	Renderer* renderer;
};