#pragma once
#include "EditableGameObject.h"
#include "GameFileLoader.h"

class LevelSwitcher : public EditableGameObject
{
	friend class LevelLoader;
public:
	LevelSwitcher(Sprite* _sprite, GameFile* _gameFile);
	~LevelSwitcher();

	bool Update(float dt) override;

	int switchToNextLevel();

	void setNextLevel(int newLevel);
	void setGameFile(GameFile*);

	void toggleEditing() override;

protected:
	GameFile* gameFile;
	int nextLevel = 0;
	bool activated = false;
};