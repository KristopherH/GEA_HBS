#pragma once
//C++
#include <string>
#include <atomic>
//DXTK

//OURS


enum class GameState {

	GS_NULL = 0,
	GS_PLAY,
	GS_MAIN_MENU,
	GS_PAUSE,
	GS_GAME_OVER,
	GS_EXIT
};


extern std::atomic<GameState> _GS; // ??? WHY ON EARTH IS THIS ATOMIC ???