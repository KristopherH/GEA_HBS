#include "SceneManager.h"
//C++

//DXTK

//OURS
#include "Scene.h"
#include "GameData.h"

SceneManager::SceneManager()
{
	currentScene = "NONE";
}

SceneManager::~SceneManager()
{
	//TODO: clear scenes map
}

void SceneManager::addScene(std::string sceneName, Scene* newScene)
{
	if (scenes[sceneName] == nullptr)
	{
		scenes[sceneName] = newScene;
	}
	if (currentScene == "NONE")
	{
		currentScene = sceneName;
		GameData::go_list = &scenes[sceneName]->go_list;
		GameData::currentCamera = scenes[sceneName]->cam;
	}
}

void SceneManager::setCurrentScene(std::string sceneName, bool removeCurrent)
{
	if (removeCurrent)
	{
		scenes[currentScene]->toBeDeleted = true;
	}
	auto scene = scenes.find(sceneName);
	if (scene != scenes.end())
	{
		currentScene = sceneName;
		GameData::go_list = &scenes[sceneName]->go_list;
		GameData::currentCamera = scenes[sceneName]->cam;
	}
}

void SceneManager::removeScene(std::string sceneName)
{
	scenes[currentScene]->toBeDeleted = true;
}

Scene* SceneManager::getScene(const std::string sceneName)
{
	return scenes[sceneName];
}

Scene* SceneManager::getCurrentScene()
{
	return scenes[currentScene];
}

std::string SceneManager::getCurrentSceneName()
{
	return currentScene;
}

void SceneManager::clearOldScenes()
{
	auto iter = scenes.begin();
	for (; iter != scenes.end(); ) {
		if (iter->second->toBeDeleted) {
			scenes.erase(iter++);
		}
		else {
			++iter;
		}
	}
}