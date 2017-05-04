#include "Input_Manager.h"
//C++
#include <string>
#include <sstream>
#ifdef DEBUG
#include <iostream>
#endif

//DXTK

//OURS
#include <GameData.h>
#include <BaseCamera.h>
#include "Button.h"

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

#ifdef ARCADE
std::map<InputLabel, Input> InputManager::key_inputs =
{
	{ InputLabel::UP, (Input)DIK_R },
	{ InputLabel::DOWN, (Input)DIK_F },
	{ InputLabel::LEFT, (Input)DIK_D },
	{ InputLabel::RIGHT, (Input)DIK_G },
	{ InputLabel::JUMP, (Input)DIK_LSHIFT },
	{ InputLabel::USE, (Input)DIK_1 },
	{ InputLabel::PAUSE, (Input)DIK_LCONTROL }
};
#else
std::map<InputLabel, Input> InputManager::key_inputs =
{
	{ InputLabel::UP, (Input)DIK_W },
	{ InputLabel::DOWN, (Input)DIK_S },
	{ InputLabel::LEFT, (Input)DIK_A },
	{ InputLabel::RIGHT, (Input)DIK_D },
	{ InputLabel::JUMP, (Input)DIK_SPACE },
	{ InputLabel::USE, (Input)DIK_RETURN },
	{ InputLabel::PAUSE, (Input)DIK_ESCAPE }
};
#endif

std::map<InputLabel, std::string> InputManager::key_effect_names =
{
	{ InputLabel::UP, "Up" },
	{ InputLabel::DOWN, "Down" },
	{ InputLabel::LEFT, "Left" },
	{ InputLabel::RIGHT,"Right" },
	{ InputLabel::JUMP, "Jump" },
	{ InputLabel::USE, "Use" },
	{ InputLabel::PAUSE, "Pause" }
};

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

	if (change_key.joinable())
		change_key.join();
}

std::string InputManager::ConvertToASCII(DWORD _key)
{
	static HKL layout = GetKeyboardLayout(0);
	static unsigned char State[256];

	if (GetKeyboardState(State) == FALSE)
		return 0;
	UINT vk = MapVirtualKeyEx(_key, 1, layout);
	char character = (vk);
	if (isalnum(character))
	{
		stringstream ss;
		string s;
		ss << character;
		ss >> s;
		return s;
	}
	if (character == ' ')
	{
		return "SPACE";
	}
	if (character == '\r')
	{
		return "ENTER";
	}
	if (character == '\x1b')
	{
		return "ESC";
	}

	return "Unknown";
}
#pragma region Mouse

bool InputManager::getMouseRight()
{
	if (mouse_state.rgbButtons[1])
		return true;

	return false;
}

bool InputManager::getMouseLeft()
{
	if (mouse_state.rgbButtons[0])
		return true;

	return false;
}

bool InputManager::getMouseMiddle()
{
		if (mouse_state.rgbButtons[2])
			return true;

	return false;
}

bool InputManager::getMouseRightPress()
{
	if (mouse_state.rgbButtons[1]
		&& !(previous_mouse_state.rgbButtons[1]))
		return true;

	return false;
}

bool InputManager::getMouseLeftPress()
{
	if (mouse_state.rgbButtons[0]
		&& !(previous_mouse_state.rgbButtons[0]))
		return true;

	return false;
}

bool InputManager::getMouseMiddlePress()
{
	if (mouse_state.rgbButtons[2]
		&& !(previous_mouse_state.rgbButtons[2]))
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



void InputManager::inputChangeHandler(InputLabel _input, Button* btn)
{
	if (change_key.joinable())
		change_key.join();

	//change_key = std::thread(&InputManager::changeInput, _input);
	change_key = (std::thread(&InputManager::changeInput, this, _input, btn));
}



void InputManager::changeInput(InputLabel _input, Button* btn)
{
	while (true)
	{
		for (int key = 0; key < sizeof(keyboard_state); key++)
		{
			if (getKeyDown(key))
			{
				key_inputs[_input] = key;
				if (btn)
				{
					btn->setText(GameData::inputManager->ConvertToASCII(key));
				}
				return;
			}
		}
		readMouse();
		if (getMouseMiddlePress() || getMouseLeftPress() || getMouseRightPress())
		{
			return;
		}
	}
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