#include "LevelEditor.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Background.h"
#include "Collision_Manager.h"
#include "MainMenu.h"
#include "SoundManager.h"
#include "SceneManager.h" 
#include "Button.h"
#include <string>
#include "Object_Factory.h"
#include "ballistics.h"
#include "Platform.h"
#include "Rope.h"
#include "LevelEditorCamera.h"
#include <algorithm>

LevelEditorScene::LevelEditorScene()
{
	Level* level1 = LevelLoader::loadLevel("Level.txt");

	player = static_cast<Player*>(ObjectFactory::createPlayer());
	int spr_ac = player->getSprite()->getSpritesAcross();
	player->setSize(new Vec2(100.0f * spr_ac, 120.0f));
	player->setPosition(level1->playerStartingPosition);
	player->setGravity(true);

	cam = new LevelEditorCamera(GameData::screen.max.x, GameData::screen.max.y, -1.0f, 10000.0f);
	Vec2 camPosition;
	camPosition += *level1->playerStartingPosition;
	camPosition *= -1;
	cam->setPosition(&camPosition);
	cam->setName("Camera");
	cam->setTag("Camera");
	cam->setSolid(false);
	cam->setPlayerTracker(player);
	cam->setPosition(&player->getPosition());
	
	GameObject* bg = ObjectFactory::createBackground(level1->backgroundStartingPos);
	go_list.push_back(bg);

	Ballistics* bullet = new Ballistics();
	go_list.push_back(bullet);
	bullet->setPosition(new Vec2(0.0f ,0.0f));
	bullet->setSize(new Vec2(100.0f, 120.0f));
	for (auto go : level1->go_list)
	{
		go_list.push_back(go);
		go = nullptr;
	}
	delete level1;
	go_list.push_back(player);

#pragma region UI

	float y = 0;
	
	Button* Playbtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Play");
	Playbtn->setSize(new Vec2(300.0f, 150.0f));
	Playbtn->setPosition(new Vec2(GameData::screen.Center().x - 800.0f, 700.0f));
	Playbtn->setOrigin(new Vec2(0.0f, 0.0f));
	Playbtn->setCallbackFunction([]() {
	});

	for (auto type : ObjectFactory::create_object)
	{
		string name;
		
		if (UINum == 0)
		{
			name = "Platforms";
		}
		else if (UINum == 1)
		{
			name = "Enemies";
		}
		else if (UINum == 2)
		{
			name = "Ladders";
		}
		else if (UINum == 3)
		{
			name = "Coin";
		}

		Sprite* sprite = new Sprite(ObjectFactory::texture_pool[type.first]);

		Button* btn = new Button(sprite, "Button", "Button", name);;
		
		btn->setPosition(new Vec2(0.0f, y));
		btn->setCallbackFunction([this, type, y]() {
			//bowties are cool
			if (!obj_selected)
			{
				//create the gameobject
				//float pos_x = (float)0.0f -
				//	((float)GameData::currentCamera->getPosition().x + ((float)GameData::currentCamera->getCameraSize().x / 2));
				//float pos_y = (float)y -
				//	((float)GameData::currentCamera->getPosition().y + ((float)GameData::currentCamera->getCameraSize().y / 2));

				float CameraXScaled = GameData::currentCamera->getPosition().x + (((float)GameData::currentCamera->getCameraSize().x) / 2) / GameData::currentCamera->getZoom();
				float CameraYScaled = GameData::currentCamera->getPosition().y + (((float)GameData::currentCamera->getCameraSize().y) / 2) / GameData::currentCamera->getZoom();

				float pos_x = (0.0f / GameData::currentCamera->getZoom()) - CameraXScaled;
				float pos_y = (y / GameData::currentCamera->getZoom()) - CameraYScaled;

				GameObject* go = type.second();
				go->setPosition(new Vec2(pos_x, pos_y));
				go_list.push_back(go);
				//set the selected object to the new object created
				obj_selected = go;
			}
		});
		btn->setSize(new Vec2(100.0f, 100.0f));
		btn->setPosition(new Vec2(0.0f, y));
		btn->setOrigin(new Vec2(0.0f, 0.0f));
		y += 100.0f;
		ui_elements.push_back(btn);
		UINum++;
	}
	Button* save = new Button(new Sprite("Button", GameData::renderer), "SaveButon", "Button", "Save");
	save->setCallbackFunction([this]() {
		char filename[MAX_PATH];

		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Save File";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn))
		{
			auto go = std::find_if(go_list.begin(), go_list.end(), [](GameObject* go)
			{
				return go->getType() == "BG";
			});

			Level* level = LevelLoader::createLevel(go_list, &player->getPosition(), &(*go)->getPosition());
			LevelLoader::saveLevel(level, std::string(filename));
			delete level;
			level = nullptr;
		}
		else
		{
			// All this stuff below is to tell you exactly how you messed up above. 
			// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
			switch (CommDlgExtendedError())
			{
			case CDERR_DIALOGFAILURE: break;
			case CDERR_FINDRESFAILURE: break;
			case CDERR_INITIALIZATION: break;
			case CDERR_LOADRESFAILURE:  break;
			case CDERR_LOADSTRFAILURE: break;
			case CDERR_LOCKRESFAILURE: break;
			case CDERR_MEMALLOCFAILURE: break;
			case CDERR_MEMLOCKFAILURE: break;
			case CDERR_NOHINSTANCE: break;
			case CDERR_NOHOOK: break;
			case CDERR_NOTEMPLATE: break;
			case CDERR_STRUCTSIZE: break;
			case FNERR_BUFFERTOOSMALL: break;
			case FNERR_INVALIDFILENAME: break;
			case FNERR_SUBCLASSFAILURE: break;
			default: break;
			}
		}
	});
	save->setSize(new Vec2(100.0f, 100.0f));
	save->setPosition(new Vec2(0.0f, y));
	save->setOrigin(new Vec2(0.0f, 0.0f));
	y += 100.0f;
	ui_elements.push_back(save);

	Button* load = new Button(new Sprite("Button", GameData::renderer), "SaveButon", "Button", "Load");
	load->setCallbackFunction([this]() {
		char filename[MAX_PATH];

		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Load FIle";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn))
		{
			for (auto go : go_list)
			{
				if (go->getTag() != "Camera"
					&& go->getTag() != "Player")
				{
					delete go;
				}
			}
			go_list.clear();

			Level* level1 = LevelLoader::loadLevel("Level.txt");

			player = static_cast<Player*>(ObjectFactory::createPlayer());

			player->setSize(new Vec2(100.0f, 120.0f));
			player->setPosition(level1->playerStartingPosition);
			player->setGravity(true);

			cam->setPlayerTracker(player);
			cam->setPosition(&player->getPosition());

			go_list.push_back(ObjectFactory::createBackground(level1->backgroundStartingPos));

			for (auto go : level1->go_list)
			{
				go_list.push_back(go);
				go = nullptr;
			}
			delete level1;

			go_list.push_back(player);
			go_list.push_back(cam);
		}
		else
		{
			// All this stuff below is to tell you exactly how you messed up above. 
			// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
			switch (CommDlgExtendedError())
			{
			case CDERR_DIALOGFAILURE: break;
			case CDERR_FINDRESFAILURE: break;
			case CDERR_INITIALIZATION: break;
			case CDERR_LOADRESFAILURE:  break;
			case CDERR_LOADSTRFAILURE: break;
			case CDERR_LOCKRESFAILURE: break;
			case CDERR_MEMALLOCFAILURE: break;
			case CDERR_MEMLOCKFAILURE: break;
			case CDERR_NOHINSTANCE: break;
			case CDERR_NOHOOK: break;
			case CDERR_NOTEMPLATE: break;
			case CDERR_STRUCTSIZE: break;
			case FNERR_BUFFERTOOSMALL: break;
			case FNERR_INVALIDFILENAME: break;
			case FNERR_SUBCLASSFAILURE: break;
			default: break;
			}
		}
	});
	load->setSize(new Vec2(100.0f, 100.0f));
	load->setPosition(new Vec2(0.0f, y));
	load->setOrigin(new Vec2(0.0f, 0.0f));
	y += 100.0f;
	ui_elements.push_back(load);

  Button* erase = new Button(new Sprite("TrashCan", GameData::renderer), "DeleteButton", "Button", "Delete");
	erase->setCallbackFunction([this]() {
		if (obj_selected)
		{
			if (obj_selected == GameData::player)
			{
				return false;
			}
			go_list.erase(std::remove_if(go_list.begin(), go_list.end(), [this](GameObject* go) {
				return obj_selected == go;
			}), go_list.end());
			delete obj_selected;
			obj_selected = nullptr;
		}
		return false;
	});
	erase->setPosition(new Vec2(0.0f, y));
	erase->setSize(new Vec2(100.0f, 100.0f));
	y += 100.0f;
	ui_elements.push_back(erase);

	Button* MainMenuBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Main Menu");
	MainMenuBtn->setSize(new Vec2(100.0f, 100.0f));
	MainMenuBtn->setPosition(new Vec2(1530.0f, 0.0f));
	MainMenuBtn->setOrigin(new Vec2(0.0f, 0.0f));
	MainMenuBtn->setCallbackFunction([]() {
		GameData::scene_manager->setCurrentScene("MainMenuScene");
		GameData::sound_manager->stopSound();
		GameData::sound_manager->playSound("MainMenu-Music.wav", false, true);
	});

	ui_elements.push_back(MainMenuBtn);
#pragma endregion
}

LevelEditorScene::~LevelEditorScene()
{
	for (auto ui_go : ui_elements)
	{
		delete ui_go;
	}
	ui_elements.clear();
}

void LevelEditorScene::Update(float dt)
{
	if (GameData::inputManager->getKeyDown(Inputs::USE))
		editing = !editing;
	if (editing)
	{
		for (auto go : go_list)
		{
			if (go->getAlive())
			{
				go->GameObject::Update(dt);
			}
		}
		cam->Update(dt);
		if (GameData::inputManager->getMouseRight() && !obj_selected)
		{
			cam->movePosition(new Vec2((float)(-GameData::inputManager->mouse_x_translation), (float)(-GameData::inputManager->mouse_y_translation)));
		}
	}
	else
	{
		Scene::Update(dt);
		cam->BaseCamera::Update(dt);
	}
	selectObject();
	moveObject();
	for (auto element : ui_elements)
	{
		element->Update(dt);
	}
}

void LevelEditorScene::Draw()
{
	Scene::Draw();
	for (auto element : ui_elements)
	{
		element->Draw();
	}
}

void LevelEditorScene::selectObject()
{
	if (GameData::inputManager->getMouseLeft()
		|| (GameData::inputManager->getMouseMiddle()))
	{
		if (!obj_selected)
		{
			GameData::inputManager->update();
			for (auto go : *GameData::go_list)
			{
				if (GameData::collsion_manager->mouseCollision(go->getBox()))
				{
					if (go->getType() == "RopeNode")
					{
						obj_selected = ((RopeNode*)(go))->parent;
						obj_select_type = ObjectSelectType::BODY;
					}
					else
					{
						obj_selected = go;
						obj_select_type = getSelectType();
					}
					break;
				}
			}
		}
	}
	else if (GameData::inputManager->getMouseRightPress())
	{
		GameData::inputManager->update();
		for (auto go : *GameData::go_list)
		{
			if (GameData::collsion_manager->mouseCollision(go->getBox()))
			{
				toggleMode(go);
				break;
			}
		}
	}
	else if(obj_selected)
	{
		obj_selected = nullptr;
		resetSelectedEdges();
	}
}

ObjectSelectType LevelEditorScene::getSelectType()
{
	if (!obj_selected)
		return ObjectSelectType::NONE;

	float edge_size = 10.0f;
	Rect edge_box = obj_selected->getBox();

	//Edge A (Left Edge)
	edge_box.max.x -= obj_selected->getSize().x - edge_size;
	if (CollisionManager::mouseCollision(edge_box))
		obj_edges_selected[ObjectEdge::A] = true;

	//Edge B (Top Edge)
	edge_box = obj_selected->getBox();
	edge_box.max.y -= obj_selected->getSize().y - edge_size;
	if (CollisionManager::mouseCollision(edge_box))
		obj_edges_selected[ObjectEdge::B] = true;

	//Edge C (Right Edge)
	edge_box = obj_selected->getBox();
	edge_box.min.x += obj_selected->getSize().x - edge_size;
	if (CollisionManager::mouseCollision(edge_box))
		obj_edges_selected[ObjectEdge::C] = true;

	//Edge D (Bottom Edge)
	edge_box = obj_selected->getBox();
	edge_box.min.y += obj_selected->getSize().y - edge_size;
	if (CollisionManager::mouseCollision(edge_box))
		obj_edges_selected[ObjectEdge::D] = true;


	//Return what edge is selected
	if (obj_edges_selected[ObjectEdge::A] && obj_edges_selected[ObjectEdge::B])
		return ObjectSelectType::TOP_LEFT;

	if (obj_edges_selected[ObjectEdge::B] && obj_edges_selected[ObjectEdge::C])
		return ObjectSelectType::TOP_RIGHT;

	if (obj_edges_selected[ObjectEdge::C] && obj_edges_selected[ObjectEdge::D])
		return ObjectSelectType::BOTTOM_RIGHT;

	if (obj_edges_selected[ObjectEdge::D] && obj_edges_selected[ObjectEdge::A])
		return ObjectSelectType::BOTTOM_LEFT;

	if (obj_edges_selected[ObjectEdge::A])
		return ObjectSelectType::LEFT;

	if (obj_edges_selected[ObjectEdge::B])
		return ObjectSelectType::TOP;

	if (obj_edges_selected[ObjectEdge::C])
		return ObjectSelectType::RIGHT;

	if (obj_edges_selected[ObjectEdge::D])
		return ObjectSelectType::BOTTOM;

	return ObjectSelectType::BODY;
}

void LevelEditorScene::moveObject()
{
	if (obj_selected && obj_select_type == ObjectSelectType::BODY)
	{
		obj_selected->movePosition(new Vec2(-GameData::inputManager->mouse_world_x_translation,
								   -GameData::inputManager->mouse_world_y_translation));
		for (auto& go : go_list)
		{
			if (go != obj_selected)
			{
				if (GameData::inputManager->getMouseMiddle())
				{
					snap(go, obj_selected);
				}
			}
		}
	}

	else if (GameData::inputManager->getMouseLeft())
	{
		scaleObject();
	}
}

void LevelEditorScene::snap(GameObject* other, GameObject* obj)
{
	if (abs(other->getBox().min.x - obj->getBox().min.x) < 10
		&& obj->getBox().min.y > other->getBox().min.y - obj->getSize().y
		&& obj->getBox().max.y < other->getBox().max.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().min.x, obj->getPosition().y));
	}

	if (abs(other->getBox().min.y - obj->getBox().min.y) < 10
		&& obj->getBox().min.x > other->getBox().min.x - obj->getSize().x
		&& obj->getBox().max.x < other->getBox().max.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().min.y));
	}


	if (abs(other->getBox().max.x - obj->getBox().min.x) < 10
		&& obj->getBox().min.y > other->getBox().min.y - obj->getSize().y
		&& obj->getBox().max.y < other->getBox().max.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().max.x, obj->getPosition().y));
	}

	if (abs(other->getBox().max.y - obj->getBox().min.y) < 10
		&& obj->getBox().min.x > other->getBox().min.x - obj->getSize().x
		&& obj->getBox().max.x < other->getBox().max.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().max.y));
	}

	if (abs(other->getBox().min.x - obj->getBox().max.x) < 10
		&& obj->getBox().min.y > other->getBox().min.y - obj->getSize().y
		&& obj->getBox().max.y < other->getBox().max.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().min.x - obj->getSize().x, obj->getPosition().y));
	}

	if (abs(other->getBox().min.y - obj->getBox().max.y) < 10
		&& obj->getBox().min.x > other->getBox().min.x - obj->getSize().x
		&& obj->getBox().max.x < other->getBox().max.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().min.y - obj->getSize().y));
	}


	if (abs(other->getBox().max.x - obj->getBox().max.x) < 10
		&& obj->getBox().min.y > other->getBox().min.y - obj->getSize().y
		&& obj->getBox().max.y < other->getBox().max.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().max.x - obj->getSize().x, obj->getPosition().y));
	}

	if (abs(other->getBox().max.y - obj->getBox().max.y) < 10
		&& obj->getBox().min.x > other->getBox().min.x - obj->getSize().x
		&& obj->getBox().max.x < other->getBox().max.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().max.y - obj->getSize().y));
	}
}

void LevelEditorScene::toggleMode(GameObject * _go)
{
	if (_go->getName() == "Platform")
	{
		Platform* platform = static_cast<Platform*>(_go);
		platform->changeType((PLATFORM_TYPE)(((int)(platform->getPlatformType()))+1));
	}
	if (_go->getType() == "RopeNode")
	{
		RopeNode* rope = static_cast<RopeNode*>(_go);
		if (GameData::inputManager->getKeyHeld(Inputs::CTRL))
		{
			rope->parent->removeNode();
		}
		else
		{
			rope->parent->addNode();
		}
	}
	else if (obj_selected && obj_select_type != ObjectSelectType::NONE)
	{
		scaleObject();
	}
}



void LevelEditorScene::scaleObject()
{
	if (!obj_selected || obj_select_type == ObjectSelectType::BODY)
		return;

	/*
		Left: obj_selected->getPosition().x + InputManager::mouse_x_translation
				obj_selected->getPosition().x + InputManager::mouse_x_translation
		Top:  obj_selected->getPosition().y + InputManager::mouse_y_translation
				obj_selected->getSize().y - InputManager::mouse_y_translation
		Right:  obj_selected->getSize().x + InputManager::mouse_x_translation;
		Bottom: obj_selected->getSize().y + InputManager::mouse_y_translation
	*/

	GameData::inputManager->readMouse();
	if (obj_select_type == ObjectSelectType::TOP_LEFT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x - InputManager::mouse_x_translation,
							obj_selected->getPosition().y - InputManager::mouse_y_translation);
		Vec2 new_size = Vec2(obj_selected->getSize().x + InputManager::mouse_x_translation,
							 obj_selected->getSize().y + InputManager::mouse_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::TOP)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x,
							obj_selected->getPosition().y - InputManager::mouse_y_translation);
		Vec2 new_size = Vec2(obj_selected->getSize().x,
							 obj_selected->getSize().y + InputManager::mouse_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::TOP_RIGHT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x,
							obj_selected->getPosition().y - InputManager::mouse_y_translation);
		Vec2 new_size = Vec2(obj_selected->getSize().x - InputManager::mouse_x_translation,
							 obj_selected->getSize().y + InputManager::mouse_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::RIGHT)
	{
		Vec2 new_size = Vec2(obj_selected->getSize().x - InputManager::mouse_x_translation,
							 obj_selected->getSize().y);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::BOTTOM_RIGHT)
	{
		Vec2 new_size = Vec2(obj_selected->getSize().x - InputManager::mouse_x_translation,
							 obj_selected->getSize().y - InputManager::mouse_y_translation);

		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::BOTTOM)
	{
		Vec2 new_size = Vec2(obj_selected->getSize().x,
							 obj_selected->getSize().y - InputManager::mouse_y_translation);

		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::BOTTOM_LEFT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x - InputManager::mouse_x_translation,
							obj_selected->getPosition().y);
		Vec2 new_size = Vec2(obj_selected->getSize().x + InputManager::mouse_x_translation,
							 obj_selected->getSize().y - InputManager::mouse_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::LEFT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x - InputManager::mouse_x_translation,
							obj_selected->getPosition().y);
		Vec2 new_size = Vec2(obj_selected->getSize().x + InputManager::mouse_x_translation,
							 obj_selected->getSize().y);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

}



void LevelEditorScene::resetSelectedEdges()
{
	for (auto& current_edge : obj_edges_selected)
		current_edge.second = false;
}
