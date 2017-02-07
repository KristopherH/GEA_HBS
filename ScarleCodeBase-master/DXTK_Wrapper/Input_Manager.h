#pragma once

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;


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
	bool getKeyDown(unsigned int key);
	bool getKeyUp(unsigned int key);
	bool getKeyHeld(unsigned int key);
#pragma endregion

#pragma region GamePad Input
	bool gamePadButtonDown(unsigned int button);
	bool gamePadButtonUp(unsigned int button);
	bool gamePadButtonHeld(unsigned int button);
#pragma endregion going to have to look more into this (pre-processor shit)

#pragma region Couple of checkers (need to double check what these would be)

#pragma endregion

};