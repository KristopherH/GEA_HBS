#include "InputManager.h"
//C++
#include <string>
#ifdef DEBUG
#include <iostream>
#endif

//DXTK

//OURS
#include <GameData.h>


unsigned char InputManager::keyboard_state[256];
unsigned char InputManager::previous_keyboard_state[256];
IDirectInput8* InputManager::user_direct_input = nullptr;
IDirectInputDevice8* InputManager::user_keyboard = nullptr;
IDirectInputDevice8* InputManager::user_mouse = nullptr;
DIMOUSESTATE InputManager::mouse_state;

int InputManager::mouse_x = 0;
int InputManager::mouse_y = 0;
int InputManager::mouse_x_translation = 0;
int InputManager::mouse_y_translation = 0;

#ifdef ARCADE
Input Inputs::UP = DIK_R;
Input Inputs::DOWN = DIK_F;
Input Inputs::LEFT = DIK_D;
Input Inputs::RIGHT = DIK_G;
Input Inputs::JUMP = DIK_LSHIFT;
Input Inputs::USE = DIK_1;
#else
Input Inputs::UP = DIK_W;
Input Inputs::DOWN = DIK_S;
Input Inputs::LEFT = DIK_A;
Input Inputs::RIGHT = DIK_D;
Input Inputs::JUMP = DIK_SPACE;
Input Inputs::USE = DIK_RETURN;
#endif

InputManager::InputManager(HWND _window, HINSTANCE _h_instance)
{
	window = _window;
	h_instance = _h_instance;
	
	SetCursorPos((int)GameData::screen.min.x, (int)GameData::screen.min.y);
}



InputManager::~InputManager()
{
	if (user_direct_input)	user_direct_input->Release();
	if (user_keyboard)		user_keyboard->Release();
	if (user_mouse)         user_mouse->Release();
}

#pragma region Mouse

bool InputManager::getMouseRight()
{
	if (mouse_state.rgbButtons[1] & 0x80)
		return true;

	return false;
}



bool InputManager::getMouseLeft()
{
	if (mouse_state.rgbButtons[0] & 0x80)
		return true;

	return false;
}



bool InputManager::getMouseMiddle()
{
		if (mouse_state.rgbButtons[2] & 0x80)
			return true;

	return false;
}

#pragma endregion


#pragma region Keyboard

bool InputManager::getKeyDown(Input _key)
{
	if (_key == 0)
	{
		OutputDebugString("Key Request Was Invalid!");
		return false;
	}

	if (keyboard_state[_key] && !previous_keyboard_state[_key]) 
		return true;

	return false;
}



bool InputManager::getKeyUp(Input _key)
{
	if (_key == 0)
	{
		OutputDebugString("Key Request Was Invalid!");
		return false;
	}

	if (!keyboard_state[_key] && previous_keyboard_state[_key])
		return true;

	return false;
}



bool InputManager::getKeyHeld(Input _key)
{
	if (_key == 0)
	{
		OutputDebugString("Key Request Was Invalid!");
		return false;
	}

	if (keyboard_state[_key]) return true;

	return false;
}

#pragma endregion


#pragma region GamePad

bool InputManager::gamePadButtonDown(unsigned int button)
{
	return false;
}



bool InputManager::gamePadButtonUp(unsigned int button)
{
	return false;
}



bool InputManager::gamePadButtonHeld(unsigned int button)
{
	return false;
}

#pragma endregion


#pragma region Checks/Inits
bool InputManager::init()
{
	HRESULT result = DirectInput8Create(h_instance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&user_direct_input, NULL);

	if (result != S_OK)
	{
		OutputDebugString("FAILED TO CREATE USER_DIRECT_INPUT IN INPUT_MANAGER.CPP\n");
		return false;
	}

	result = user_direct_input->CreateDevice(GUID_SysKeyboard, &user_keyboard, NULL);
	if (result != S_OK)
	{
		OutputDebugString("FAILED TO CREATE USER_KEYBOARD IN INPUT_MANAGER.CPP\n");
		return false;
	}

	result = user_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (result != S_OK)
	{
		OutputDebugString("FAILED TO SET DATA FORMAT FOR USER_KEYBOARD IN INPUT_MANAGER.CPP\n");
		return false;
	}

	result = user_keyboard->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (result != S_OK)
	{
		OutputDebugString("FAILED TO CREATE SET COOPERAIVE LEVEL FOR USER_KEYBOARD IN INPUT_MANAGER.CPP\n");
		return false;
	}
	readKeyboard();
	
	result = user_direct_input->CreateDevice(GUID_SysMouse, &user_mouse, NULL);
	if (result != S_OK)
	{
		OutputDebugString("FAILED TO CREATE USER_MOUSE IN INPUT_MANAGER.CPP\n");
		return false;
	}

	result = user_mouse->SetDataFormat(&c_dfDIMouse);
	if (result != S_OK)
	{
		OutputDebugString("FAILED TO SET DATA FORMAT FOR USER_MOUSE IN INPUT_MANAGER.CPP\n");
		return false;
	}

	result = user_mouse->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (result != S_OK)
	{
		OutputDebugString("FAILED TO CREATE SET COOPERAIVE LEVEL FOR USER_MOUSE IN INPUT_MANAGER.CPP\n");
		return false;
	}
	readMouse();
	
	return true;
}



bool InputManager::readKeyboard()
{
	memcpy(previous_keyboard_state, keyboard_state, sizeof(unsigned char) * 256);

	ZeroMemory(&keyboard_state, sizeof(keyboard_state));

	HRESULT result = user_keyboard->GetDeviceState(sizeof(keyboard_state),
		(LPVOID)&keyboard_state);

	if (result != S_OK)
	{
		OutputDebugString("KEYBOARD HAS LOST FOCUS, TRYING TO REGAIN CONNECTION\n");

		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			user_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}



bool InputManager::readMouse()
{
	//memcpy(previous_mouse_state, mouse_state, sizeof(DIMOUSESTATE));
	/*
		TODO: FORCE THE MOUSE TO STAY WITHIN WINDOW BOUNDS
				CHECK FOR BUTTON CLICK AND NOT JUST POSITION
				SOME OTHER SHIT PROBABLY 5:38 IT'S TIME TO SLEEP

	*/
	//ZeroMemory(&mouse_state, sizeof(mouse_state));

	HRESULT result = user_mouse->GetDeviceState(sizeof(DIMOUSESTATE),
		(LPVOID)&mouse_state);

	if (FAILED(result))
	{
		OutputDebugString("KEYBOARD HAS LOST FOCUS, TRYING TO REGAIN CONNECTION\n");

		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			user_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}



void InputManager::update()
{
	readKeyboard();
	readMouse();

	#pragma region Mouse Position
	POINT mouse_pos;
	GetPhysicalCursorPos(&mouse_pos);
	ScreenToClient(window, &mouse_pos); // This function doeas hat you were trying to do and excludes the borders

	mouse_x_translation = mouse_x - mouse_pos.x;
	mouse_y_translation = mouse_y - mouse_pos.y;

	mouse_x = mouse_pos.x;
	mouse_y = mouse_pos.y;

	if (mouse_x < 0)
	{
		mouse_x = 0;
		mouse_x_translation = 0;
	}

	if (mouse_y < 0)
	{
		mouse_y = 0;
		mouse_y_translation = 0;
	}

	if (mouse_x > (int)(GameData::screen.max.x))
	{
		mouse_x = (int)GameData::screen.max.x;
		mouse_x_translation = 0;
	}

	if (mouse_y > (int)(GameData::screen.max.y))
	{
		mouse_y = (int)GameData::screen.max.y;
		mouse_y_translation = 0;
	}

	
	#ifdef DEBUG
	std::cout << "Mouse X: " << mouse_x << std::endl;
	std::cout << "Mouse Y: " << mouse_y << std::endl;
	std::cout << "Mouse X Change: " << mouse_x_translation << std::endl;
	std::cout << "Mouse Y Change: " << mouse_y_translation << std::endl;
	#endif
	#pragma endregion
}

#pragma endregion
