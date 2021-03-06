#pragma once
//C++
#include <string>
#include <map>
//DXTK

//OURS

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void addScene(std::string sceneName, Scene* newScene);
	void setCurrentScene(std::string sceneName, bool deleteCurrent = true);

	Scene* getScene(std::string sceneName);
	Scene* getCurrentScene();

	std::string getCurrentSceneName();

	void removeScene(std::string sceneName);
	void clearOldScenes();

private:
	std::map<std::string, Scene*> scenes;
	std::string currentScene;
};