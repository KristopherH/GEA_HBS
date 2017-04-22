#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "../DXTK_Wrapper/CustomMath.h"

class InputManager;
class Renderer;
class CollisionManager;
class GameController;
class SceneManager;
class GameObject;
class BaseCamera;
class SoundManager;
struct Inputs;


struct GameData
{
	//float m_dt; ??? Why is this commented away ???
	//GameState m_gS; // game state
 
	static InputManager* inputManager;
	static Renderer* renderer;
	static CollisionManager* collsion_manager;
	static SceneManager* scene_manager;
	static GameController* game_controller;
	static SoundManager* sound_manager;
	static std::vector<GameObject*>* go_list;
	static Inputs input;

	static BaseCamera* currentCamera;

	static Rect screen;

};