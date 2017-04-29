#pragma once

#include "Scene.h"

class PauseOptions : public Scene
{
public:
	PauseOptions();
	virtual ~PauseOptions() = default;

	virtual void Update(float dt) override;
	virtual void Draw() override;

protected:

};

