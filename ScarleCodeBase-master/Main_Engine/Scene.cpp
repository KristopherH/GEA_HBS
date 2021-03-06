#include "Scene.h"
#include "BaseCamera.h"
#include "GameData.h"

Scene::Scene()
{
	//create a base camera
	//cam = new BaseCamera(GameData::renderer->getWindowWidth(), GameData::renderer->getWindowHeight(), -1.0f, 10000.0f);
	cam = new BaseCamera(GameData::screen.maxCorner.x, GameData::screen.maxCorner.y, -1.0f, 10000.0f);
	//mainCamera->SetPosition(new Vec2(player->GetPosition().x + player->GetSize().x, player->GetPosition().y - player->GetSize().y));
	cam->setName("Camera");
	cam->setTag("Camera");
	cam->setSolid(false);
	go_list.push_back(cam);
	GameData::currentCamera = cam;
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
	for (int i = 0; i < go_list.size(); i++)
	{
		if (go_list[i]->getAlive())
		{
			go_list[i]->gravityUpdate();
			go_list[i]->Update(dt);
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
