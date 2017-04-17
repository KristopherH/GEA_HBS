#include "Scene.h"
#include "BaseCamera.h"
#include "GameData.h"

Scene::Scene()
{
	//create a base camera
	cam = new BaseCamera(GameData::renderer->getWindowWidth(), GameData::renderer->getWindowHeight(), -1.0f, 10000.0f);
	//mainCamera->SetPosition(new Vec2(player->GetPosition().x + player->GetSize().x, player->GetPosition().y - player->GetSize().y));
	cam->setName("Camera");
	cam->setTag("Camera");
	cam->setSolid(false);
	go_list.push_back(cam);
}

Scene::~Scene()
{
	//Clears the go_list
	for (auto go : go_list)
	{
		delete go;
	}
	go_list.clear();
}

void Scene::Update(float dt)
{
	for (auto go : go_list)
	{
		if (go->getAlive())
		{
			go->gravityUpdate();
			go->Update(dt);
		}
	}
}

void Scene::Draw()
{
	for (const auto go : go_list)
	{
		if (go->getAlive())
			go->Draw();
	}
}

BaseCamera * Scene::getCamera()
{
	return cam;
}
