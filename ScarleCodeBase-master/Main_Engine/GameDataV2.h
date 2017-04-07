#pragma once
//#include "../DXTK_Wrapper/DXTKRenderer.h"
//#include "../DXTK_Wrapper/Input_Manager.h"
//#include "../DXTK_Wrapper/Collision_Manager.h"
//#include "../Main_Engine/Game_Controller.h"
#include <vector>

//#include "Input_Manager.h"
 
//#include "SceneManager.h"
 
class InputManager;
class Renderer;
class CollisionManager;
class GameController;
class GameObjectV2;
struct Inputs;
 

struct GameDataV2
{
 
	//float m_dt;
	//GameState m_gS; // game state

 
	static InputManager* inputManager;
	static Renderer* renderer;
	static CollisionManager* collsion_manager;
	static GameController* game_controller;
	static std::vector<GameObjectV2*> go_list;
	static Inputs input;
 
};