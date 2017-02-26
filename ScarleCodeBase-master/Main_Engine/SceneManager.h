#pragma once
#include <string>
#include <atomic>

enum class GameState {

	GS_NULL = 0,
	GS_PLAY,
	GS_MAIN_MENU,
	GS_PAUSE,
	GS_GAME_OVER,
	GS_EXIT
};


extern std::atomic<GameState> _GS;