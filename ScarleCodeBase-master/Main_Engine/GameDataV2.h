#pragma once
//C++
#include <vector>

//DXTK

//OURS
 
class InputManager;
class Renderer;
class CollisionManager;
class GameController;
class GameObjectV2;
struct Inputs;
 

struct GameDataV2
{
 
	//float m_dt; ??? Why is this commented away ???
	//GameState m_gS; // game state

 
	static InputManager* inputManager;
	static Renderer* renderer;
	static CollisionManager* collsion_manager;
	static GameController* game_controller;
	static std::vector<GameObjectV2*> go_list;
	static Inputs input;
	
	// ??? whys is this not a rect ???
	static unsigned int screen_width;
	static unsigned int screen_height;
	static unsigned int screen_pos_x;
	static unsigned int screen_pos_y;
 
};