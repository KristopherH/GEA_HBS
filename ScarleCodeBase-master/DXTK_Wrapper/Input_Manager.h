#pragma once
#include <dinput.h>

class InputManager
{
public:
	InputManager() = delete;
	InputManager(HWND _window, HINSTANCE _h_instance);
	~InputManager();


#pragma region Mouse Input
	bool getMouseRightDown();
	bool getMouseRightUp();
	bool getMouseRightHeld();
	bool getMouseLeftDown();
	bool getMouseLeftUp();
	bool getMouseLeftHeld();
	bool getMouseMiddleDown();
	bool getMouseMiddleUp();
	bool getMouseMiddleHeld();
#pragma endregion

#pragma region Keyboard Input
	bool getKeyDown(char _key);
	bool getKeyUp(char _key);
	bool getKeyHeld(char _key);
#pragma endregion

#pragma region GamePad Input
	bool gamePadButtonDown(unsigned int button);
	bool gamePadButtonUp(unsigned int button);
	bool gamePadButtonHeld(unsigned int button);
#pragma endregion going to have to look more into this (pre-processor shit)

#pragma region Couple of checkers (need to double check what these would be)
	bool init();
	bool readKeyboard();
#pragma endregion

private:

	int convertCharToDinput(char _input);

	unsigned char keyboard_state[256];
	unsigned char previous_keyboard_state[256];
	IDirectInput8* user_direct_input = nullptr;
	IDirectInputDevice8* user_keyboard = nullptr;
	HWND window;
	HINSTANCE h_instance;
};