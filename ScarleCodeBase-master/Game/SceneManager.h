#pragma once
#include <string>
#include <atomic>

enum class GameScene
{

	PLAY,
	EXIT,
	PAUSE,
	MAINMENU

};

extern std::atomic<GameScene> gameScene;


class SceneManager
{
	
public:
	SceneManager();
	~SceneManager();
	GameScene m_GS;

}