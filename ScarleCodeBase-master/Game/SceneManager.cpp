#include "SceneManager.h"

/**< Queued Game scene. The next scene to be processed as determined by user input. */
std::atomic<GameScene> gameScene = GameScene::MAINMENU;