#pragma once

#include "Scene.h"
#include "Button.h"

class PauseMenu : public Scene
{
public:
	PauseMenu();
	virtual ~PauseMenu() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:
	Button* ResumeBtn;
	Button* OptnsBtn;
	Button* ExitBtn;
	bool pauseOptns = false;
};
