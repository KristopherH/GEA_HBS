#include "GameData.h"
//C++

//DXTK

//OURS
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "../DXTK_Wrapper/Input_Manager.h"
#include "../DXTK_Wrapper/Collision_Manager.h"
#include "../Main_Engine/Game_Controller.h"
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