#include "Input_Manager.h"
//C++
#include <string>
#ifdef DEBUG
#include <iostream>
#endif

//DXTK

//OURS
#include <GameData.h>
#include <BaseCamera.h>

unsigned char InputManager::keyboard_state[256];
unsigned char InputManager::previous_keyboard_state[256];
IDirectInput8* InputManager::user_direct_input = nullptr;
IDirectInputDevice8* InputManager::user_keyboard = nullptr;
IDirectInputDevice8* InputManager::user_mouse = nullptr;
DIMOUSESTATE InputManager::mouse_state;
DIMOUSESTATE InputManager::previous_mouse_state;

int InputManager::mouse_x = 0;
int InputManager::mouse_y = 0;
int InputManager::mouse_x_translation = 0;
int InputManager::mouse_y_translation = 0;
float InputManager::mouse_world_x = 0.0f;
float InputManager::mouse_world_y = 0.0f;
float InputManager::mouse_world_x_translation = 0;
float InputManager::mouse_world_y_translation = 0;
int InputManager::mouse_scroll = 0;
int InputManager::mouse_scroll_translation = 0;

Input up_key = DIK_W;
Input down_key = DIK_S;
Input left_key = DIK_A;
Input right_key = DIK_D;
Input jump_key = DIK_SPACE;
Input pause_key = DIK_P;

#ifdef ARCADE
Input Inputs::UP = DIK_R;
Input Inputs::DOWN = DIK_F;
Input Inputs::LEFT = DIK_D;
Input Inputs::RIGHT = DIK_G;
Input Inputs::JUMP = DIK_LSHIFT;
Input Inputs::USE = DIK_1;
Input Inputs::CTRL = DIK_LCONTROL;
#else
Input Inputs::UP = up_key;
Input Inputs::DOWN = down_key;
Input Inputs::LEFT = left_key;
Input Inputs::RIGHT = right_key;
Input Inputs::PAUSE = pause_key;
Input Inputs::JUMP = jump_key;
Input Inputs::USE = DIK_RETURN;
Input Inputs::CTRL = DIK_LCONTROL;
#endif

InputManager::InputManager(HWND _window, HINSTANCE _h_instance)
{
	window = _window;
	h_instance = _h_instance;
	
	SetCursorPos((int)GameData::screen.minCorner.x, (int)GameData::screen.minCorner.y);
}

InputManager::~InputManager()
{
	if (user_direct_input)	user_direct_input->Release();
	if (user_keyboard)		user_keyboard->Release();
	if (user_mouse)         user_mouse->Release();
}

void InputManager::newUpKey(Input _Key)
{
	up_key = _Key;
	Inputs::UP = _Key;	
}

int InputManager::ConvertToASCII(DWORD _key)
{
	static HKL layout = GetKeyboardLayout(0);
	static unsigned char State[256];

	if (GetKeyboardState(State) == FALSE)
		return 0;
	UINT vk = MapVirtualKeyEx(_key, 1, layout);
	return vk;
}

void InputManager::newDownKey(Input _Key)
{
	down_key = _Key;
	Inputs::DOWN = _Key;
}

void InputManager::newLeftKey(Input _Key)
{
	left_key = _Key;
	Inputs::LEFT = _Key;
}

void InputManager::newRightKey(Input _Key)
{
	right_key = _Key;
	Inputs::RIGHT = _Key;
}

void InputManager::newJumpKey(Input _Key)
{
	jump_key = _Key;
	Inputs::JUMP = _Key;
}

void InputManager::newPauseKey(Input _Key)
{
	pause_key = _Key;
	Inputs::PAUSE = _Key;
}

Input InputManager::getUpKey()
{
	return up_key;
}

Input InputManager::getDownKey()
{
	return down_key;
}

Input InputManager::getLeftKey()
{
	return left_key;
}

Input InputManager::getRightKey()
{
	return right_key;
}

Input InputManager::getJumpKey()
{
	return jump_key;
}

Input InputManager::getPauseKey()
{
	return pause_key;
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

bool InputManager::getMouseRightPress()
{
	if (mouse_state.rgbButtons[1] & 0x80
		&& !(previous_mouse_state.rgbButtons[1] & 0x80))
		return true;

	return false;
}

bool InputManager::getMouseLeftPress()
{
	//readMouse();
	if (mouse_state.rgbButtons[0]
		&& !(previous_mouse_state.rgbButtons[0]))
		return true;

	return false;
}

bool InputManager::getMouseMiddlePress()
{
	if (mouse_state.rgbButtons[2] & 0x80
		&& !(previous_mouse_state.rgbButtons[2] & 0x80))
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

	previous_mouse_state = mouse_state;

	HRESULT result = user_mouse->GetDeviceState(sizeof(DIMOUSESTATE),
		(LPVOID)&mouse_state);

	if (FAILED(result))
	{
		OutputDebugString("MOUSE HAS LOST FOCUS, TRYING TO REGAIN CONNECTION\n");

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

	mouse_scroll_translation = mouse_scroll - mouse_state.lZ;
	mouse_scroll = mouse_state.lZ;

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

	if (mouse_x > (int)(GameData::screen.maxCorner.x))
	{
		mouse_x = (int)GameData::screen.maxCorner.x;
		mouse_x_translation = 0;
	}

	if (mouse_y > (int)(GameData::screen.maxCorner.y))
	{
		mouse_y = (int)GameData::screen.maxCorner.y;
		mouse_y_translation = 0;
	}

	float CameraXScaled = GameData::currentCamera->getPosition().x + (((float)GameData::currentCamera->getCameraSize().x) / 2 ) / GameData::currentCamera->getZoom();
	float CameraYScaled = GameData::currentCamera->getPosition().y + (((float)GameData::currentCamera->getCameraSize().y) / 2 ) / GameData::currentCamera->getZoom();

	InputManager::mouse_world_x_translation = InputManager::mouse_world_x - ((GameData::inputManager->mouse_x / GameData::currentCamera->getZoom()) - CameraXScaled);
	InputManager::mouse_world_y_translation = InputManager::mouse_world_y - ((GameData::inputManager->mouse_y / GameData::currentCamera->getZoom()) - CameraYScaled);

	InputManager::mouse_world_x = (GameData::inputManager->mouse_x / GameData::currentCamera->getZoom()) - CameraXScaled;
	InputManager::mouse_world_y = (GameData::inputManager->mouse_y / GameData::currentCamera->getZoom()) - CameraYScaled;

	

	#ifdef DEBUG
	std::cout << "Mouse world X: " << InputManager::mouse_world_x <<  "    Mouse world Y: " << InputManager::mouse_world_y << std::endl;
	#endif
	#pragma endregion
}

#pragma endregion

#pragma region Gual

void InputManager::stringInputBackspace()
{
	if (readingInputStream)
	{
		backspace = true;
	}
}

void InputManager::stringInputReturn()
{
	if (readingInputStream)
	{
		enter = true;
	}
}

void InputManager::stringInputAddKey(char ch)
{
	if (readingInputStream)
	{
		mtx.lock();
		inputStream.push(ch);
		mtx.unlock();
	}
}

void InputManager::startReading()
{
	readingInputStream = true;

}

char InputManager::getLatestInput()
{
	if (readingInputStream)
	{
		if (backspace)
		{
			backspace = false;
			return -1;
		}
		if (enter)
		{
			enter = false;
			return -2;
		}
		mtx.lock();
		char ch;
		if (inputStream.size() > 0)
		{
			ch = inputStream.front();
			inputStream.pop();
		}
		else
		{
			ch = -3;
		}
		mtx.unlock();
		return ch;

	}
}

void InputManager::stopReading()
{
	readingInputStream = false;
}

#pragma endregion