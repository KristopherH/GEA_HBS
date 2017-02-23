#include "Input_Manager.h"

unsigned char InputManager::keyboard_state[256];
unsigned char InputManager::previous_keyboard_state[256];
IDirectInput8* InputManager::user_direct_input = nullptr;
IDirectInputDevice8* InputManager::user_keyboard = nullptr;

InputManager::InputManager(HWND _window, HINSTANCE _h_instance)
{
	window = _window;
	h_instance = _h_instance;
}



InputManager::~InputManager()
{
	if (user_direct_input)	user_direct_input->Release();
	if (user_keyboard)		user_keyboard->Release();
}

#pragma region Mouse

bool InputManager::getMouseRightDown()
{
	return false;
}



bool InputManager::getMouseRightUp()
{
	return false;
}



bool InputManager::getMouseRightHeld()
{
	return false;
}



bool InputManager::getMouseLeftDown()
{
	return false;
}



bool InputManager::getMouseLeftUp()
{
	return false;
}



bool InputManager::getMouseLeftHeld()
{
	return false;
}



bool InputManager::getMouseMiddleDown()
{
	return false;
}



bool InputManager::getMouseMiddleUp()
{
	return false;
}



bool InputManager::getMouseMiddleHeld()
{
	return false;
}

#pragma endregion


#pragma region Keyboard

bool InputManager::getKeyDown(char _key)
{
	readKeyboard();
	unsigned int key = convertCharToDinput(_key);

	if (key == 0)
	{
		OutputDebugString("Key Request Was Invalid!");
		return false;
	}

	if (keyboard_state[key] && !previous_keyboard_state[key]) 
		return true;

	return false;
}



bool InputManager::getKeyUp(char _key)
{
	readKeyboard();
	unsigned int key = convertCharToDinput(_key);

	if (key == 0)
	{
		OutputDebugString("Key Request Was Invalid!");
		return false;
	}

	if (keyboard_state[key] != previous_keyboard_state[key])
		return true;

	return false;
}



bool InputManager::getKeyHeld(char _key)
{
	readKeyboard();
	unsigned int key = convertCharToDinput(_key);

	if (key == 0)
	{
		OutputDebugString("Key Request Was Invalid!");
		return false;
	}

	if (keyboard_state[key]) return true;

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



int InputManager::convertCharToDinput(char _input)
{
	switch (_input)
	{
	case 'W':
	case 'w':
		return 0x11;
		break;

	case 'A':
	case 'a':
		return 0x1E;
		break;

	case 'S':
	case 's':
		return 0x1f;
		break;

	case 'D':
	case 'd':
		return 0x20;
		break;

	case '_':
		return 0x39;
		break;

	default:
		return 0;
		break;
	}

	return 0;
}

#pragma endregion