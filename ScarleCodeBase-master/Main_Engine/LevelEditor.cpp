#include "LevelEditor.h"
#include "GameData.h"
//DXTK
#if defined _DXTK_
#include "..\DXTK_Wrapper/InputManager.h"
#include "..\DXTK_Wrapper/LevelLoader.h"
#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/InputManager.h"
#include "../Phyre/Code/LevelLoader.h"
#endif

#include "Player.h"
#include "Background.h"
#include "Collision_Manager.h"
#include "Button.h"
#include <string>
#include "Object_Factory.h"

LevelEditorScene::LevelEditorScene()
{
	std::vector<Sprite*> BGs;
	BGs.push_back(new Sprite("11_background", GameData::renderer));
	BGs.push_back(new Sprite("10_distant_clouds", GameData::renderer));
	BGs.push_back(new Sprite("09_distant_clouds1", GameData::renderer));
	BGs.push_back(new Sprite("08_clouds", GameData::renderer));
	BGs.push_back(new Sprite("07_huge_clouds", GameData::renderer));
	BGs.push_back(new Sprite("06_hill2", GameData::renderer));
	BGs.push_back(new Sprite("05_hill1", GameData::renderer));
	BGs.push_back(new Sprite("04_bushes", GameData::renderer));
	BGs.push_back(new Sprite("03_distant_trees", GameData::renderer));
	BGs.push_back(new Sprite("02_trees and bushes", GameData::renderer));
	BGs.push_back(new Sprite("01_ground", GameData::renderer));

	Background* bg = new Background(BGs, cam);
	go_list.push_back(bg);

	Sprite* sprite1 = new Sprite("player_sprite", GameData::renderer);
	player = new Player(sprite1, "Player", "Player");

	player->setSize(new Vec2(100.0f, 120.0f));
	player->setPosition(new Vec2(-475.0f, 350.0f));
	player->setGravity(true);

	player->setGravityTag("Slow Platform");
	player->setGravityTag("Sticky Platform");
	player->setGravityTag("Speed Platform");
	player->setGravityTag("Conveyor Left");
	player->setGravityTag("Conveyor Right");
	player->setGravityTag("Jump Platform");
	player->setGravityTag("Standard Platform");

	Level* level1 = LevelLoader::loadLevel("Level.txt");
	player->setPosition(level1->playerStartingPosition);
	for (auto go : level1->go_list)
	{
		go_list.push_back(go);
		go = nullptr;
	}
	delete level1;

	cam->setPlayerTracker(player);

	go_list.push_back(player);

#pragma region UI

	float y = 0;
	
	for (auto type : creatableObjectTypes)
	{
		Sprite* sprite = new Sprite(type, GameData::renderer);
		Button* btn = new Button(sprite, "Button", "Button");
		btn->setPosition(new Vec2(0.0f, y));
		btn->setCallbackFunction([this, type, y]() {
			//bowties are cool
			if (!obj_selected)
			{
				//create the gameobject
				float mouse_world_x = (float)0.0f - 
					((float)GameData::currentCamera->getPosition().x + ((float)GameData::currentCamera->getCameraSize().x / 2));
				float mouse_world_y = (float)y - 
					((float)GameData::currentCamera->getPosition().y + ((float)GameData::currentCamera->getCameraSize().y / 2));

				GameObject* go = ObjectFactory::createPlatform();
				go->setPosition(new Vec2(mouse_world_x, mouse_world_y));
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

#ifndef _PHYRE_
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

			go_list.push_back(ObjectFactory::createBackground());

			Sprite* sprite1 = new Sprite("player_sprite", GameData::renderer);
			player = new Player(sprite1, "Player", "Player");

			player->setSize(new Vec2(100.0f, 120.0f));
			player->setPosition(new Vec2(-475.0f, 350.0f));
			player->setGravity(true);

			player->setGravityTag("Slow Platform");
			player->setGravityTag("Sticky Platform");
			player->setGravityTag("Speed Platform");
			player->setGravityTag("Conveyor Left");
			player->setGravityTag("Conveyor Right");
			player->setGravityTag("Jump Platform");
			player->setGravityTag("Standard Platform");

			Level* level1 = LevelLoader::loadLevel(filename);
			player->setPosition(level1->playerStartingPosition);
			for (auto go : level1->go_list)
			{
				go_list.push_back(go);
				go = nullptr;
			}
			delete level1;

			GameData::currentCamera->setPlayerTracker(player);

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
#endif // _PHYRE_

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
