#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "GameObjectV2.h"

class Scene
{
	friend class SceneManager;
public:
	Scene();
	virtual ~Scene();

	virtual void Update(float dt);

	virtual void Draw();

	virtual BaseCamera* getCamera();

	bool toBeDeleted;

protected:
	std::vector<GameObjectV2*> go_list;
	BaseCamera* cam;
};