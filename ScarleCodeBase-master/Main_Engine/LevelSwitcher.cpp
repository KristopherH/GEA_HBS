#include "LevelSwitcher.h"
#include "Collision_Manager.h"
#include "Player.h"
#include "Button.h"
#include "Object_Factory.h"

LevelSwitcher::LevelSwitcher( Sprite* _sprite, GameFile* _gameFile)
	:gameFile(_gameFile), EditableGameObject(_sprite)
{
	nextLevel = 0;
	activated = false;
	setSize(new Vec2(100, 100));
	setType("LevelSwitcher");
	setName("LevelSwitcher");
}

LevelSwitcher::~LevelSwitcher()
{

}

bool LevelSwitcher::Update(float dt)
{
	if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
	{
		if (GameData::inputManager->getKeyDown(InputManager::key_inputs[InputLabel::USE]))
		{
			//switch to next level
			activated = true;
		}
	}
	return EditableGameObject::Update(dt);
}

int LevelSwitcher::switchToNextLevel()
{
	if (activated)
	{
		if (nextLevel > gameFile->levels.size()-1)
		{
			nextLevel = 0;
		}
		activated = false;
		return nextLevel;
	}
	return -1;
}

void LevelSwitcher::setNextLevel(int newLevel)
{
	nextLevel = newLevel;
}

void LevelSwitcher::setGameFile(GameFile* _gameFile)
{
	gameFile = _gameFile;
	if (nextLevel > gameFile->levels.size()-1)
	{
		nextLevel = 0;
	}
}

void LevelSwitcher::toggleEditing()
{
	EditableGameObject::toggleEditing();
	if (editing)
	{
		if (nextLevel > gameFile->levels.size()-1)
		{
			nextLevel = 0;
		}
		std::string levelString = nextLevel != -2 ? "Level:" + gameFile->levels[nextLevel].name : "Game End";
		Button* newLevelNumber = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"", "NULL", levelString);
		newLevelNumber->setSize(new Vec2(max(size.x, 100), 50));
		newLevelNumber->setPosition(new Vec2(position.x, position.y + size.y));
		newLevelNumber->setCallbackFunction([this, newLevelNumber]()
		{
			return;
		});
		newLevelNumber->setScreenSpace(false);
		ui_elements.push_back(newLevelNumber);

		Button* plusLevel = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"", "NULL", "");
		plusLevel->setSize(new Vec2(50, 50));
		plusLevel->setPosition(new Vec2(position.x + newLevelNumber->getSize().x, position.y + size.y));
		plusLevel->setCallbackFunction([this, newLevelNumber]()
		{
			nextLevel++;
			if (nextLevel == -1)
			{
				nextLevel = 0;
			}
			else if (nextLevel > gameFile->levels.size()-1)
			{
				nextLevel = -2;
			}
			std::string levelString = nextLevel != -2 ? "Level:" + gameFile->levels[nextLevel].name : "Game End";
			newLevelNumber->setText(levelString);
			return;
		});
		plusLevel->setScreenSpace(false);
		ui_elements.push_back(plusLevel);

		Button* minusLevel = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"", "NULL", "");
		minusLevel->setSize(new Vec2(50, 50));
		minusLevel->setPosition(new Vec2(position.x - minusLevel->getSize().x, position.y + size.y));
		minusLevel->setCallbackFunction([this, newLevelNumber]()
		{
			nextLevel--;
			if (nextLevel <= -2)
			{
				nextLevel = gameFile->levels.size() - 1;
			}
			else if (nextLevel < 0)
			{
				nextLevel = -2;
			}
			
			std::string levelString = nextLevel != -2 ? "Level:" + gameFile->levels[nextLevel].name : "Game End";
			newLevelNumber->setText(levelString);
			return;
		});
		minusLevel->setScreenSpace(false);
		ui_elements.push_back(minusLevel);
	}
}
