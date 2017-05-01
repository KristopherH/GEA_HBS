#pragma once
//C++

//DXTK

//OURS
#include "Scene.h"
#include "Background.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:

};