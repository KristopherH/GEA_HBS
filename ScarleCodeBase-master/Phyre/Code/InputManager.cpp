#include "InputManager.h"
//C++
#include <string>/*
#ifdef DEBUG
#include <iostream>
#endif*/

//DXTK

//OURS
//#include <GameData.h>

int InputManager::mouse_x = 0;
int InputManager::mouse_y = 0;
int InputManager::mouse_x_translation = 0;
int InputManager::mouse_y_translation = 0;
PInputMapper* InputManager::input_mapper = nullptr;

#ifdef ARCADE
Input Inputs::UP = DIK_R;
Input Inputs::DOWN = DIK_F;
Input Inputs::LEFT = DIK_D;
Input Inputs::RIGHT = DIK_G;
Input Inputs::JUMP = DIK_LSHIFT;
Input Inputs::USE = DIK_1;
#elif defined _DXTK_
Input Inputs::UP = DIK_W;
Input Inputs::DOWN = DIK_S;
Input Inputs::LEFT = DIK_A;
Input Inputs::RIGHT = DIK_D;
Input Inputs::JUMP = DIK_SPACE;
Input Inputs::USE = DIK_RETURN;
#elif defined _PHYRE_
Input Inputs::UP = Phyre::PInputs::PInputBase::InputChannel_Button_Up;
Input Inputs::DOWN = Phyre::PInputs::PInputBase::InputChannel_Button_Down;
Input Inputs::LEFT = Phyre::PInputs::PInputBase::InputChannel_Button_Left;
Input Inputs::RIGHT = Phyre::PInputs::PInputBase::InputChannel_Button_Right;
Input Inputs::JUMP = Phyre::PInputs::PInputBase::InputChannel_Button_X;
Input Inputs::USE = Phyre::PInputs::PInputBase::InputChannel_Button_Square;
#endif

InputManager::InputManager(Phyre::PFramework::PInputMapper* _input_mapper)
{
	input_mapper = _input_mapper;
}

#pragma region Mouse

bool InputManager::getMouseRight()
{
	//if (mouse_state.rgbButtons[1] & 0x80)
		return true;

	return false;
}



bool InputManager::getMouseLeft()
{
	//if (mouse_state.rgbButtons[0] & 0x80)
		return true;

	return false;
}



bool InputManager::getMouseMiddle()
{
	//if (mouse_state.rgbButtons[2] & 0x80)
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

	//if (keyboard_state[_key] && !previous_keyboard_state[_key])
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

	//if (!keyboard_state[_key] && previous_keyboard_state[_key])
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

	//if (keyboard_state[_key]) return true;

	return false;
}

#pragma endregion


#pragma region GamePad

bool InputManager::gamePadButtonPress(Input _input)
{
	if (input_mapper->checkAndClearJoypadButton(_input))
	{
		return true;
	}
	return false;
}



bool InputManager::gamePadButtonUp(Input _input)
{
	return false;
}



bool InputManager::gamePadButtonHeld(Input _input)
{
	return false;
}

#pragma endregion


#pragma region Checks/Inits
bool InputManager::init()
{
	return false;
}



bool InputManager::readKeyboard()
{
	return false;
}



bool InputManager::readMouse()
{
	return false;
}



void InputManager::update()
{
	readKeyboard();
	readMouse();
}

#pragma endregion
