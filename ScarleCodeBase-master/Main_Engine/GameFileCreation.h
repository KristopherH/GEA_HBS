#pragma once
#include "Scene.h"
#include <vector>
#include "Button.h"
#include "Texture.h"
#include "GameData.h"
#include "GameFileLoader.h"
#include "LevelEditor.h"

class GameFileCreation : public Scene
{
public:
	GameFileCreation();
	virtual ~GameFileCreation();

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:
	void initButtons();

	std::vector<GameObject> LevelsList;
	Texture* buttonTexture;
	Texture* deleteButtonTexture;	
	GameFile* gameFile;
	bool redoButtons = true;
};