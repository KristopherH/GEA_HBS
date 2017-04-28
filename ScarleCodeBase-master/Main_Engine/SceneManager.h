#pragma once
//C++
#include <string>
#include <map>
//DXTK

//OURS

class Scene;

enum class GameState {

	GS_NULL = 0,
	GS_PLAY,
	GS_MAIN_MENU,
	GS_PAUSE,
	GS_GAME_OVER,
	GS_EXIT
};
extern GameState _GS;

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

	void clearOldScenes();

private:
	std::map<std::string, Scene*> scenes;
	std::string currentScene;
};