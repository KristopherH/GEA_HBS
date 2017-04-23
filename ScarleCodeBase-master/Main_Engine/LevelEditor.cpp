#include "LevelEditor.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Background.h"
#include "Collision_Manager.h"
#include "Button.h"
#include <string>
#include "Object_Factory.h"
#include "Platform.h"

LevelEditorScene::LevelEditorScene()
{
	Level* level1 = LevelLoader::loadLevel("Level.txt");

	player = static_cast<Player*>(ObjectFactory::createPlayer());

	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(level1->playerStartingPosition);
	player->setGravity(true);

	cam->setPlayerTracker(player);
	cam->setPosition(&player->getPosition());

	go_list.push_back(ObjectFactory::createBackground());

	for (auto go : level1->go_list)
	{
		go_list.push_back(go);
		go = nullptr;
	}
	delete level1;

	go_list.push_back(player);

#pragma region UI

	float y = 0;
	
	for (auto type : ObjectFactory::create_object)
	{
		Sprite* sprite = new Sprite(ObjectFactory::texture_pool[type.first]);
		Button* btn = new Button(sprite, "Button", "Button");

		btn->setPosition(new Vec2(0.0f, y));
		btn->setCallbackFunction([this, type, y]() {
			//bowties are cool
			if (!obj_selected)
			{
				//create the gameobject
				float pos_x = (float)0.0f - 
					((float)GameData::currentCamera->getPosition().x + ((float)GameData::currentCamera->getCameraSize().x / 2));
				float pos_y = (float)y - 
					((float)GameData::currentCamera->getPosition().y + ((float)GameData::currentCamera->getCameraSize().y / 2));

				GameObject* go = type.second();
				go->setPosition(new Vec2(pos_x, pos_y));
				go_list.push_back(go);
				//set the selected object to the new object created
				obj_selected = go;
			}
		});
		btn->setPosition(new Vec2(0.0f, y));
		btn->setSize(new Vec2(100.0f, 100.0f));
		y += 100.0f;
		ui_elements.push_back(btn);
	}
 Button* save = new Button(new Sprite("Button", GameData::renderer), "SaveButon", "Button");
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
			Level* level = LevelLoader::createLevel(go_list, &player->getPosition());
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
	save->setPosition(new Vec2(0.0f, y));
	save->setSize(new Vec2(100.0f, 100.0f));
	y += 100.0f;
	ui_elements.push_back(save);

	Button* load = new Button(new Sprite("Button", GameData::renderer), "SaveButon", "Button");
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

			go_list.push_back(ObjectFactory::createBackground());

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
	load->setPosition(new Vec2(0.0f, y));
	load->setSize(new Vec2(100.0f, 100.0f));
	y += 100.0f;
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
	Scene::Update(dt);
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
	if (GameData::inputManager->getMouseLeft())
	{
		if (!obj_selected)
		{
			GameData::inputManager->update();
			for (auto go : *GameData::go_list)
			{
				if (GameData::collsion_manager->mouseCollision(go->getBox()))
				{
					obj_selected = go;
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
			}
		}
	}
	else if(obj_selected)
	{
		obj_selected = nullptr;
	}
}



void LevelEditorScene::moveObject()
{
	if (obj_selected)
	{
		obj_selected->movePosition(new Vec2(-GameData::inputManager->mouse_x_translation,
								   -GameData::inputManager->mouse_y_translation));
	}
}

void LevelEditorScene::toggleMode(GameObject * _go)
{
	if (_go->getType() == "Platform")
	{
		Platform* platform = static_cast<Platform*>(_go);
		platform->changeType((PLATFORM_TYPE)(((int)(platform->getPlatformType()))+1));
	}
}
