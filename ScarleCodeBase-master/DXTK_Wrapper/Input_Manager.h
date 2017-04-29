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
	static Input PAUSE;
	static Input CTRL;
};

class InputManager
{
public:
	InputManager() = delete;
	InputManager(HWND _window, HINSTANCE _h_instance);
	~InputManager();

	void newUpKey(Input _Key);
	void newDownKey(Input _Key);
	void newLeftKey(Input _Key);
	void newRightKey(Input _Key);
	void newJumpKey(Input _Key);
	void newPauseKey(Input _Key);
	
	Input getUpKey() { return up_key; };
	Input getDownKey() { return down_key; };
	Input getLeftKey() { return left_key; };
	Input getRightKey() { return right_key; };
	Input getJumpKey() { return jump_key; };
	Input getPausepKey() { return pause_key; };

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

	Input up_key = (int)DIK_W;
	Input down_key = DIK_S;
	Input left_key = DIK_A;
	Input right_key = DIK_D;
	Input jump_key = DIK_SPACE;
	Input pause_key = DIK_P;
};