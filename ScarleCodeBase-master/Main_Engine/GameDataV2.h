#pragma once
//#include "../DXTK_Wrapper/DXTKRenderer.h"
//#include "../DXTK_Wrapper/Input_Manager.h"
//#include "../DXTK_Wrapper/Collision_Manager.h"
//#include "../Main_Engine/Game_Controller.h"
#include <vector>

class InputManager;
class Renderer;
class CollisionManager;
class GameController;
class GameObjectV2;

struct GameDataV2
{
	static InputManager* inputManager;
	static Renderer* renderer;
	static CollisionManager* collsion_manager;
	static GameController* game_controller;
	static std::vector<GameObjectV2*> go_list;
};