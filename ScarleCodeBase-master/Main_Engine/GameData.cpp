#include "GameData.h"
//C++


//DXTK
#if defined _DXTK_
#include "..\DXTK_Wrapper\InputManager.h"
#include "..\DXTK_Wrapper\Renderer.h"
#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/InputManager.h"
#include "../Phyre/Code/Renderer.h"
#endif


//OURS
#include "Game_Controller.h"
#include "Collision_Manager.h"
#include "SceneManager.h"
#include "BaseCamera.h"

InputManager* GameData::inputManager = nullptr;
Renderer* GameData::renderer = nullptr;
CollisionManager* GameData::collsion_manager = nullptr;
GameController* GameData::game_controller = nullptr;
SceneManager* GameData::scene_manager = nullptr;

BaseCamera* GameData::currentCamera = nullptr;

std::vector<GameObject*>* GameData::go_list;

Rect GameData::screen = Rect(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
