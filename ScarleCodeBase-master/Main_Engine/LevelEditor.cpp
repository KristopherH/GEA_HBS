#include "LevelEditor.h"
#include "GameDataV2.h"
#include "Input_Manager.h"
#include "LevelLoader.h"
#include "PlayerV2.h"
#include "Background.h"

LevelEditorScene::LevelEditorScene()
{
	std::vector<Sprite*> BGs;
	BGs.push_back(new Sprite("11_background", GameDataV2::renderer));
	BGs.push_back(new Sprite("10_distant_clouds", GameDataV2::renderer));
	BGs.push_back(new Sprite("09_distant_clouds1", GameDataV2::renderer));
	BGs.push_back(new Sprite("08_clouds", GameDataV2::renderer));
	BGs.push_back(new Sprite("07_huge_clouds", GameDataV2::renderer));
	BGs.push_back(new Sprite("06_hill2", GameDataV2::renderer));
	BGs.push_back(new Sprite("05_hill1", GameDataV2::renderer));
	BGs.push_back(new Sprite("04_bushes", GameDataV2::renderer));
	BGs.push_back(new Sprite("03_distant_trees", GameDataV2::renderer));
	BGs.push_back(new Sprite("02_trees and bushes", GameDataV2::renderer));
	BGs.push_back(new Sprite("01_ground", GameDataV2::renderer));

	Background* bg = new Background(BGs, cam);
	go_list.push_back(bg);

	Sprite* sprite1 = new Sprite("player_sprite", GameDataV2::renderer);
	player = new PlayerV2(sprite1, "Player", "Player");

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
	return;
}

void LevelEditorScene::Update(float dt)
{
	Scene::Update(dt);
	if (GameDataV2::inputManager->getKeyHeld(Inputs::DOWN))
	{
		char filename[MAX_PATH];

		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Select a File, yo!";
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
	}
}

void LevelEditorScene::Draw()
{
	Scene::Draw();
}
