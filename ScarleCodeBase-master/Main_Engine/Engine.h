#pragma once
//C++
#include <vector>
#include <memory>

//External

//Internal

//
class GameObject;

class Engine
{
public:
	Engine();
	~Engine();

	bool tick();

private:
	std::vector<std::unique_ptr<GameObject>> go_list;
};