#include "GameFileCreation.h"
#include <algorithm>
#include "SceneManager.h"
#include "SoundManager.h"

GameFileCreation::GameFileCreation()
{
	buttonTexture = new Texture("Button", GameData::renderer);
	deleteButtonTexture = new Texture("Button", GameData::renderer);
	gameFile = GameFileLoader::loadGame();
	if (!gameFile)
	{
		std::vector<GameObject*> empty;
		gameFile = GameFileLoader::createGameFIle(*LevelLoader::createLevel(
			empty, new Vec2(0.0f, 0.0f),
			new Vec2(0.0f, 0.0f), "Intro"), 3);
		gameFile->levels[0].path = ".\\GameFiles\\level.lvl";
	}
	initButtons();
}

GameFileCreation::~GameFileCreation()
{
}

void GameFileCreation::Update(float dt)
{
	if (redoButtons)
	{
		initButtons();
	}
	Scene::Update(dt);
}

void GameFileCreation::Draw()
{
	Scene::Draw();
}

void GameFileCreation::initButtons()
{
	for (auto go : go_list)
	{
		if (go->getTag() != "Camera")
		delete go;
	}
	go_list.clear();

	Button* MainMenuBtn = new Button(new Sprite("Button", GameData::renderer), "button1", "Button", "Main Menu");
	MainMenuBtn->setSize(new Vec2(100.0f, 100.0f));
	MainMenuBtn->setPosition(new Vec2(1530.0f, 0.0f));
	MainMenuBtn->setOrigin(new Vec2(0.0f, 0.0f));
	MainMenuBtn->setCallbackFunction([]() {
		GameData::scene_manager->setCurrentScene("MainMenuScene");
		GameData::sound_manager->stopSound();
		GameData::sound_manager->playSound("MainMenu-Music.wav", false, true);
	});

	go_list.push_back(MainMenuBtn);

	Button* title = new Button(new Sprite("Button", GameData::renderer),
		"Title", "Button", "Game File Creation");
	title->setSize(new Vec2(300.0f, 100.0f));
	title->setPosition(new Vec2(0.0f, 0.0f));
	title->setCallbackFunction([]()
	{
		//nothing
	});
	go_list.push_back(title);

	//Button* load = new Button(new Sprite(buttonTexture), "Title", "Button", "Load GameFile");
	//load->setPosition(new Vec2(0.0f, 0.0f));
	//load->setCallbackFunction([]()
	//{

	//});
	//go_list.push_back(load);

	Button* save = new Button(new Sprite(buttonTexture), "Title", "Button", "Save GameFile");
	save->setSize(new Vec2(300.0f, 100.0f));
	save->setPosition(&(GameData::screen.max - save->getSize()));
	save->setCallbackFunction([this]()
	{
		//save file in default position
		GameFileLoader::saveGameFile(gameFile);

	});
	go_list.push_back(save);

	Vec2 pos;
	pos += Vec2(10.0f, 200.0f);
	int levelNumber = 0;
	for (auto& level : gameFile->levels)
	{
		std::string btnName = std::to_string(levelNumber);
		btnName.append(": ");
		btnName.append(level.name);
		Button* btn = new Button(new Sprite(buttonTexture), "levelButton", "Button", btnName);
		btn->setSize(new Vec2(400.0f, 50.0f));
		btn->setPosition(&pos);
		std::string levelPath = level.path;
		btn->setCallbackFunction([levelPath]()
		{
			//go to levelEditor scene with this level
			GameData::scene_manager->addScene("LevelEditor", new LevelEditorScene(levelPath));
			GameData::scene_manager->setCurrentScene("LevelEditor", false);
		});
		go_list.push_back(btn);

		Button* btn1 = new Button(new Sprite(deleteButtonTexture), "levelButtonDelete", "Button", "X");
		btn1->setSize(new Vec2(50.0f, 50.0f));
		btn1->setPosition(&(pos + Vec2(410.0f, 0.0f)));
		btn1->setCallbackFunction([this, levelNumber]()
		{
			//delete this level and redo the buttons
			gameFile->levels.erase(gameFile->levels.begin() + levelNumber);
			redoButtons = true;
		});
		pos += Vec2(0.0f, 110.0f);
		go_list.push_back(btn1);
		levelNumber++;
	}

	Button* btn = new Button(new Sprite(buttonTexture), "levelButton", "Button", "Add new level");
	btn->setSize(new Vec2(400.0f, 50.0f));
	btn->setPosition(&pos);
	btn->setCallbackFunction([this]()
	{
		//Open selection screen to add level
		char filename[MAX_PATH];

		OPENFILENAME ofn;
		ZeroMemory(&filename, sizeof(filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = "Level Files\0*.lvl";
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Load FIle";
		ofn.Flags = OFN_DONTADDTORECENT | OFN_CREATEPROMPT | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn))
		{
			Level* level1 = LevelLoader::loadLevel(filename);
			std::string tmp= filename;
			std::string start = "\\GameFiles\\";
			std::string end = ".lvl";
			std::string token = tmp.substr(tmp.find(start) + 1, tmp.find(end) - tmp.find(start) - 1); // token is whatever is inbetween ()
			std::string path = ".\\";
			path.append(token);
			path.append(end);
			level1->path = path;
			gameFile->addLevel(*level1);
			redoButtons = true;
			delete level1;
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
	go_list.push_back(btn);
	redoButtons = false;
}
