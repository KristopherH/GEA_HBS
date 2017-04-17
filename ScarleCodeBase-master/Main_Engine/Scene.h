#pragma once
//C++
#include <vector>

//DXTK

//OURS
#include "GameObject.h"

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
	std::vector<GameObject*> go_list;
	BaseCamera* cam;
};