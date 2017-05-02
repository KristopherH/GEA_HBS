#pragma once
//C++

//DXTK
#include <dinput.h>
#include <queue>
#include <mutex>
#include <map>

//OURS


using Input = int;

enum class InputLabel
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	USE,
	PAUSE,
	CTRL
};

class InputManager
{
public:
	InputManager() = delete;
	InputManager(HWND _window, HINSTANCE _h_instance);
	~InputManager();

	static std::map<InputLabel, Input> key_inputs;

	void changeInput(InputLabel _input, Input _key);
	int ConvertToASCII(DWORD _key);

#pragma region Mouse Input
	bool getMouseRight();
	bool getMouseLeft();
	bool getMouseMiddle();

	bool getMouseRightPress();
	bool getMouseLeftPress();
	bool getMouseMiddlePress();
#pragma endregion

#pragma region Keyboard Input
	bool getKeyDown(Input _key);
	bool getKeyUp(Input _key);
	bool getKeyHeld(Input _key);
#pragma endregion

#pragma region GamePad Input
	bool gamePadButtonDown(unsigned int button);
	bool gamePadButtonUp(unsigned int button);
	bool gamePadButtonHeld(unsigned int button);
#pragma endregion going to have to look more into this (pre-processor shit)

#pragma region Couple of checkers (need to double check what these would be)
	bool init();
	bool readKeyboard();
	bool readMouse();
	void update();
#pragma endregion

#pragma region Gual, give this a proper name please...

	std::mutex mtx;
	void stringInputBackspace();
	void stringInputReturn();
	void stringInputAddKey(char ch);
	void startReading();
	char getLatestInput();
	void stopReading();

	bool readingInputStream;
	std::queue<char> inputStream;
	bool enter = false;
	bool backspace = false;
#pragma endregion


	static int mouse_x;
	static int mouse_y;
	static int mouse_x_translation;
	static int mouse_y_translation;
	static float mouse_world_x;
	static float mouse_world_y;
	static float mouse_world_x_translation;
	static float mouse_world_y_translation;
	static int mouse_scroll;
	static int mouse_scroll_translation;

private:
	//int convertCharToDinput(char _input);

	static unsigned char keyboard_state[256];
	static unsigned char previous_keyboard_state[256];
	static IDirectInput8* user_direct_input;
	static IDirectInputDevice8* user_keyboard;
	static IDirectInputDevice8* user_mouse;
	static DIMOUSESTATE mouse_state;
	static DIMOUSESTATE previous_mouse_state;

	HWND window;
	HINSTANCE h_instance;

};