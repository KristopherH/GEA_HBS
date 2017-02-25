#include "GameDataV2.h"
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "../DXTK_Wrapper/Input_Manager.h"
#include "../DXTK_Wrapper/Collision_Manager.h"
#include "../Main_Engine/Game_Controller.h"

InputManager* GameDataV2::inputManager = nullptr;
Renderer* GameDataV2::renderer = nullptr;
CollisionManager* GameDataV2::collsion_manager = nullptr;
GameController* GameDataV2::game_controller = nullptr;
std::vector<GameObjectV2*> GameDataV2::go_list;