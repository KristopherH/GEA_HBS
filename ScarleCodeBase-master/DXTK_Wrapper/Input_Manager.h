#pragma once
//C++

//DXTK
#include <dinput.h>

//OURS


using Input = int;

struct Inputs
{
	static Input UP;
	static Input DOWN;
	static Input LEFT;
	static Input RIGHT;
	static Input JUMP;
	static Input USE;
};

class InputManager
{
public:
	InputManager() = delete;
	InputManager(HWND _window, HINSTANCE _h_instance);
	~InputManager();

	void newUpKey(Input _Key);
	int ConvertToASCII(DWORD _key);
	void newDownKey(Input _Key);
	void newLeftKey(Input _Key);
	void newRightKey(Input _Key);
	void newJumpKey(Input _Key);
	void newPauseKey(Input _Key);
	
	Input getUpKey();
	Input getDownKey();
	Input getLeftKey();
	Input getRightKey();
	Input getJumpKey();
	Input getPauseKey();

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

	static int mouse_x;
	static int mouse_y;
	static int mouse_x_translation;
	static int mouse_y_translation;
	static float mouse_world_x;
	static float mouse_world_y;

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