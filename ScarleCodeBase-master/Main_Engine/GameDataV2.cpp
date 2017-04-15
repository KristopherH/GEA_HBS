#include "GameDataV2.h"
//C++

//DXTK

//OURS
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "../DXTK_Wrapper/Input_Manager.h"
#include "../DXTK_Wrapper/Collision_Manager.h"
#include "../Main_Engine/Game_Controller.h"
#include "SceneManager.h"
#include "BaseCamera.h"

InputManager* GameDataV2::inputManager = nullptr;
Renderer* GameDataV2::renderer = nullptr;
CollisionManager* GameDataV2::collsion_manager = nullptr;
GameController* GameDataV2::game_controller = nullptr;
SceneManager* GameDataV2::scene_manager = nullptr;

BaseCamera* GameDataV2::currentCamera = nullptr;

std::vector<GameObjectV2*>* GameDataV2::go_list;

Rect GameDataV2::screen = Rect(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
