#include "GameFileLoader.h"
#include "LevelEditor.h"
//C++
#include <string>
#include <algorithm>

//Wrapper
#include "Input_Manager.h"
#include "LevelLoader.h"
#include "Collision_Manager.h"

//OURS
#include "GameData.h"
#include "Player.h"
#include "Background.h"
#include "MainMenu.h"
#include "SoundManager.h"
#include "SceneManager.h" 
#include "Button.h"
#include "Object_Factory.h"
#include "ballistics.h"
#include "Platform.h"
#include "Rope.h"
#include "LevelEditorCamera.h"
#include "TextBox.h"
#include "Enemy.h"
#include "EnemyWaypoint.h"
#include "PlatformWaypoint.h"
#include "EditableGameObject.h"
#include "LevelSwitcher.h"
#include "GameFileCreation.h"


LevelEditorScene::LevelEditorScene(GameFile* _gameFile, int lvlNumber)
	:gameFile(_gameFile), levelNumber(lvlNumber)
{
	Level* level1 = &gameFile->levels[levelNumber];
	levelName = level1->name;
	player = static_cast<Player*>(ObjectFactory::createPlayer());

	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(level1->playerStartingPosition);
	player->setGravity(true);

	cam = new LevelEditorCamera(GameData::screen.maxCorner.x, GameData::screen.maxCorner.y, -1.0f, 10000.0f);
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

	for (auto go : level1->go_list)
	{
		go_list.push_back(go);
		go = nullptr;
	}
	//delete level1;
	go_list.push_back(player);

#pragma region UI

	TextBox* rename = new TextBox(new Sprite("Button", GameData::renderer), "button1", "Button", levelName);
	rename->setSize(new Vec2(300.0f, 60.0f));
	rename->setPosition(new Vec2(GameData::screen.maxCorner.x / 2 - rename->getSize().x / 2, 0.0f));
	rename->setOrigin(new Vec2(0.0f, 0.0f));
	rename->setOnEnterCallback([this, rename]()
	{
		levelName = rename->getText();
	});
	ui_elements.push_back(rename);

	Button* BackBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Back");
	BackBtn->setSize(new Vec2(100.0f, 100.0f));
	BackBtn->setPosition(new Vec2(GameData::screen.maxCorner.x - BackBtn->getSize().x, 0.0f));
	BackBtn->setOrigin(new Vec2(0.0f, 0.0f));
	BackBtn->setCallbackFunction([]() {
		GameData::scene_manager->addScene("GameFileCreation", new GameFileCreation());
		GameData::scene_manager->setCurrentScene("GameFileCreation");
	});
	ui_elements.push_back(BackBtn);

	float y = 0;
	for (auto type : ObjectFactory::create_object)
	{
		float buttonSize = GameData::screen.maxCorner.y / ObjectFactory::texture_pool.size();
		Sprite* sprite = new Sprite(ObjectFactory::texture_pool[type.first]);

		Button* btn = new Button(sprite, "Button", "Button", ObjectFactory::names[type.first], false);
		btn->setPosition(new Vec2(0.0f, y));
		btn->setCallbackFunction([this, type, y]() {
			//bowties are cool, very coool TODO: remove stupid comments like this one
			if (!obj_selected)
			{
				float CameraXScaled = GameData::currentCamera->getPosition().x + (((float)GameData::currentCamera->getCameraSize().x) / 2) / GameData::currentCamera->getZoom();
				float CameraYScaled = GameData::currentCamera->getPosition().y + (((float)GameData::currentCamera->getCameraSize().y) / 2) / GameData::currentCamera->getZoom();

				float pos_x = (0.0f / GameData::currentCamera->getZoom()) - CameraXScaled;
				float pos_y = (y / GameData::currentCamera->getZoom()) - CameraYScaled;

				GameObject* go = type.second();
				if (go->getType() == "LevelSwitcher")
				{
					LevelSwitcher* lvlSwitch = static_cast<LevelSwitcher*>(go);
					lvlSwitch->setGameFile(gameFile);
					go = lvlSwitch;
				}
				go->setPosition(new Vec2(pos_x, pos_y));
				go_list.push_back(go);
				//set the selected object to the new object created
				obj_selected = go;
			}
		});
		btn->setSize(new Vec2(buttonSize, buttonSize));
		btn->setPosition(new Vec2(0.0f, y));
		btn->setOrigin(new Vec2(0.0f, 0.0f));
		y += buttonSize;
		ui_elements.push_back(btn);
		UINum++;
	}

	y = 0.0f;
	Button* erase = new Button(new Sprite("TrashCan", GameData::renderer), "DeleteButton", "Button", "Delete", false);
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
	erase->setSize(new Vec2(100.0f, 100.0f));
	y += erase->getSize().y;
	erase->setPosition(new Vec2(GameData::screen.maxCorner.x - erase->getSize().x, GameData::screen.maxCorner.y - y));
	erase->setOrigin(new Vec2(0.0f, 0.0f));
	ui_elements.push_back(erase);

	Button* save = new Button(new Sprite("Button", GameData::renderer), "SaveButon", "Button", "Save");
	save->setCallbackFunction([this]() {
		auto go = std::find_if(go_list.begin(), go_list.end(), [](GameObject* go)
		{
			return go->getType() == "BG";
		});

		Level* level = LevelLoader::createLevel(go_list, &player->getPosition(), &(*go)->getPosition(), levelName);
		LevelLoader::saveLevel(level, std::string(gameFile->levels[levelNumber].path));
		GameFileLoader::saveGameFile(gameFile);
		delete level;
		level = nullptr;
	});
	save->setSize(new Vec2(100.0f, 100.0f));
	y += save->getSize().y;
	save->setPosition(new Vec2(GameData::screen.maxCorner.x - save->getSize().x, GameData::screen.maxCorner.y - y));
	save->setOrigin(new Vec2(0.0f, 0.0f));
	ui_elements.push_back(save);

	Button* load = new Button(new Sprite("Button", GameData::renderer), "LoadButon", "Button", "Copy From");
	load->setCallbackFunction([this]() {
		char filename[MAX_PATH];

		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = "Level Files\0*.lvl";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Copy from FIle";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_CREATEPROMPT | OFN_NOCHANGEDIR;

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

			Level* level1 = LevelLoader::loadLevel(filename);

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
	y += load->getSize().y;
	load->setPosition(new Vec2(GameData::screen.maxCorner.x - load->getSize().x, GameData::screen.maxCorner.y - y));
	load->setOrigin(new Vec2(0.0f, 0.0f));
	ui_elements.push_back(load);

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
		for (int i = 0; i < go_list.size(); i ++)
		{
			if (go_list[i]->getAlive())
			{
				EditableGameObject* ed_go = dynamic_cast<EditableGameObject*>(go_list[i]);
				if (ed_go)
				{
					ed_go->EditableGameObject::Update(dt);
				}
				else
				{
					go_list[i]->GameObject::Update(dt);
				}
			}
		}
		cam->Update(dt);
		if (GameData::inputManager->getMouseRight())
		{
			cam->movePosition(new Vec2((float)(-GameData::inputManager->mouse_x_translation / cam->getZoom()),
				(float)(-GameData::inputManager->mouse_y_translation / cam->getZoom())));
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
#ifdef ARCADE
			GameData::inputManager->update();
#endif
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
				EditableGameObject* ed_go = dynamic_cast<EditableGameObject*>(go);
				if (ed_go)
				{
					for (auto& sub_go : ed_go->ui_elements)
					{
						if (GameData::collsion_manager->mouseCollision(sub_go->getBox()))
						{
							if (sub_go->getType() == "Waypoint")
							{
								obj_selected = sub_go;
								obj_select_type = ObjectSelectType::BODY;
							}
						}
					}
				}
			}
		}
	}
	else if (GameData::inputManager->getMouseRightPress())
	{
#ifdef ARCADE
		GameData::inputManager->update();
#endif
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
	edge_box.maxCorner.x -= obj_selected->getSize().x - edge_size;
	if (CollisionManager::mouseCollision(edge_box))
		obj_edges_selected[ObjectEdge::A] = true;

	//Edge B (Top Edge)
	edge_box = obj_selected->getBox();
	edge_box.maxCorner.y -= obj_selected->getSize().y - edge_size;
	if (CollisionManager::mouseCollision(edge_box))
		obj_edges_selected[ObjectEdge::B] = true;

	//Edge C (Right Edge)
	edge_box = obj_selected->getBox();
	edge_box.minCorner.x += obj_selected->getSize().x - edge_size;
	if (CollisionManager::mouseCollision(edge_box))
		obj_edges_selected[ObjectEdge::C] = true;

	//Edge D (Bottom Edge)
	edge_box = obj_selected->getBox();
	edge_box.minCorner.y += obj_selected->getSize().y - edge_size;
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
	if (abs(other->getBox().minCorner.x - obj->getBox().minCorner.x) < 10
		&& obj->getBox().minCorner.y > other->getBox().minCorner.y - obj->getSize().y
		&& obj->getBox().maxCorner.y < other->getBox().maxCorner.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().minCorner.x, obj->getPosition().y));
	}

	if (abs(other->getBox().minCorner.y - obj->getBox().minCorner.y) < 10
		&& obj->getBox().minCorner.x > other->getBox().minCorner.x - obj->getSize().x
		&& obj->getBox().maxCorner.x < other->getBox().maxCorner.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().minCorner.y));
	}


	if (abs(other->getBox().maxCorner.x - obj->getBox().minCorner.x) < 10
		&& obj->getBox().minCorner.y > other->getBox().minCorner.y - obj->getSize().y
		&& obj->getBox().maxCorner.y < other->getBox().maxCorner.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().maxCorner.x, obj->getPosition().y));
	}

	if (abs(other->getBox().maxCorner.y - obj->getBox().minCorner.y) < 10
		&& obj->getBox().minCorner.x > other->getBox().minCorner.x - obj->getSize().x
		&& obj->getBox().maxCorner.x < other->getBox().maxCorner.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().maxCorner.y));
	}

	if (abs(other->getBox().minCorner.x - obj->getBox().maxCorner.x) < 10
		&& obj->getBox().minCorner.y > other->getBox().minCorner.y - obj->getSize().y
		&& obj->getBox().maxCorner.y < other->getBox().maxCorner.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().minCorner.x - obj->getSize().x, obj->getPosition().y));
	}

	if (abs(other->getBox().minCorner.y - obj->getBox().maxCorner.y) < 10
		&& obj->getBox().minCorner.x > other->getBox().minCorner.x - obj->getSize().x
		&& obj->getBox().maxCorner.x < other->getBox().maxCorner.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().minCorner.y - obj->getSize().y));
	}


	if (abs(other->getBox().maxCorner.x - obj->getBox().maxCorner.x) < 10
		&& obj->getBox().minCorner.y > other->getBox().minCorner.y - obj->getSize().y
		&& obj->getBox().maxCorner.y < other->getBox().maxCorner.y + obj->getSize().y)
	{
		obj->setPosition(new Vec2(other->getBox().maxCorner.x - obj->getSize().x, obj->getPosition().y));
	}

	if (abs(other->getBox().maxCorner.y - obj->getBox().maxCorner.y) < 10
		&& obj->getBox().minCorner.x > other->getBox().minCorner.x - obj->getSize().x
		&& obj->getBox().maxCorner.x < other->getBox().maxCorner.x + obj->getSize().x)
	{
		obj->setPosition(new Vec2(obj->getPosition().x, other->getBox().maxCorner.y - obj->getSize().y));
	}
}

void LevelEditorScene::toggleMode(GameObject * _go)
{
	EditableGameObject* go;
	if (_go->getType() == "RopeNode")
	{
		RopeNode* rope = static_cast<RopeNode*>(_go);
		go = dynamic_cast<EditableGameObject*>(rope->parent);
	}
	else
	{
		go = dynamic_cast<EditableGameObject*>(_go);
	}
	if (go)
	{
		go->toggleEditing();
	}
}



void LevelEditorScene::scaleObject()
{
	if (!obj_selected || obj_select_type == ObjectSelectType::BODY)
		return;

	GameData::inputManager->readMouse();
	if (obj_select_type == ObjectSelectType::TOP_LEFT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x - InputManager::mouse_world_x_translation,
							obj_selected->getPosition().y - InputManager::mouse_world_y_translation);
		Vec2 new_size = Vec2(obj_selected->getSize().x + InputManager::mouse_world_x_translation,
							 obj_selected->getSize().y + InputManager::mouse_world_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::TOP)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x,
							obj_selected->getPosition().y - InputManager::mouse_world_y_translation);
		Vec2 new_size = Vec2(obj_selected->getSize().x,
							 obj_selected->getSize().y + InputManager::mouse_world_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::TOP_RIGHT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x,
							obj_selected->getPosition().y - InputManager::mouse_world_y_translation);
		Vec2 new_size = Vec2(obj_selected->getSize().x - InputManager::mouse_world_x_translation,
							 obj_selected->getSize().y + InputManager::mouse_world_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::RIGHT)
	{
		Vec2 new_size = Vec2(obj_selected->getSize().x - InputManager::mouse_world_x_translation,
							 obj_selected->getSize().y);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::BOTTOM_RIGHT)
	{
		Vec2 new_size = Vec2(obj_selected->getSize().x - InputManager::mouse_world_x_translation,
							 obj_selected->getSize().y - InputManager::mouse_world_y_translation);

		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::BOTTOM)
	{
		Vec2 new_size = Vec2(obj_selected->getSize().x,
							 obj_selected->getSize().y - InputManager::mouse_world_y_translation);

		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::BOTTOM_LEFT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x - InputManager::mouse_world_x_translation,
							obj_selected->getPosition().y);
		Vec2 new_size = Vec2(obj_selected->getSize().x + InputManager::mouse_world_x_translation,
							 obj_selected->getSize().y - InputManager::mouse_world_y_translation);

		obj_selected->setPosition(&new_pos);
		obj_selected->setSize(&new_size);
	}

	if (obj_select_type == ObjectSelectType::LEFT)
	{
		Vec2 new_pos = Vec2(obj_selected->getPosition().x - InputManager::mouse_world_x_translation,
							obj_selected->getPosition().y);
		Vec2 new_size = Vec2(obj_selected->getSize().x + InputManager::mouse_world_x_translation,
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
