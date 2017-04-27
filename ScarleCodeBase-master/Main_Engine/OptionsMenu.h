#pragma once

#include "Scene.h"

class OptionsMenu : public Scene
{
public:
	OptionsMenu();
	virtual ~OptionsMenu() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:
std::vector<Sprite*> optnMenuSprites;
};
