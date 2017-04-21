#include "InputManager.h"
//C++
#include <string>
////Phyre
#include <Framework/PhyreFrameworkInput.h>
#include <Framework/PhyreFrameworkInputFilter.h>
#include <Framework/PhyreFrameworkInputDevice.h>
#include <Framework/PhyreFrameworkInputMotion.h>
#include <Framework/PhyreFrameworkInputMotionController.h>
#include <Framework/PhyreFrameworkInputTouch.h>
#include <Framework/PhyreFrameworkInputMapper.h>

int InputManager::mouse_x = 0;
int InputManager::mouse_y = 0;
int InputManager::mouse_x_translation = 0;
int InputManager::mouse_y_translation = 0;
Phyre::PFramework::PInputMapper* InputManager::input_mapper = nullptr;
Input InputManager::previous_key = Input::InputChannel_Empty;

#ifdef _PHYRE_
Input Inputs::NONE = Input::InputChannel_Empty;
Input Inputs::UP = Input::InputChannel_Button_Up;
Input Inputs::DOWN = Input::InputChannel_Button_Down;
Input Inputs::LEFT = Input::InputChannel_Button_Left;
Input Inputs::RIGHT = Input::InputChannel_Button_Right;
Input Inputs::JUMP = Input::InputChannel_Button_X;
Input Inputs::USE = Input::InputChannel_Button_Circle;
#endif

#pragma region Mouse
bool InputManager::getMouseRight()
{
	//if (mouse_state.rgbButtons[1] & 0x80)
	//return true;

	return false;
}



bool InputManager::getMouseLeft()
{
	//if (mouse_state.rgbButtons[0] & 0x80)
	//return true;

	return false;
}



bool InputManager::getMouseMiddle()
{
	//if (mouse_state.rgbButtons[2] & 0x80)
	//return true;

	return false;
}

#pragma endregion


#pragma region Keyboard

bool InputManager::getKeyDown(Input _key)
{
	if (_key == Inputs::NONE)
	{
		PHYRE_PRINTF("Key Request Was Invalid!");
		return false;
	}

	if ((_key != previous_key) && input_mapper->checkAndClearJoypadButton(_key))
	{
		previous_key = _key;
		return true;
	}

	return false;
}



bool InputManager::getKeyUp(Input _key)
{
	if (_key == Inputs::NONE)
	{
		PHYRE_PRINTF("Key Request Was Invalid!");
		return false;
	}

	if ((_key == previous_key) && !input_mapper->checkAndClearJoypadButton(_key))
	{
		previous_key = Input::InputChannel_Empty;
		return true;
	}

	return false;
}



bool InputManager::getKeyHeld(Input _key)
{
	if (_key == Inputs::NONE)
	{
		PHYRE_PRINTF("Key Request Was Invalid!");
		return false;
	}
	
	if (input_mapper->checkAndClearJoypadButton(_key))
	{
		previous_key = _key;
		return true;
	}

	return false;
}

#pragma endregion


#pragma region GamePad

bool InputManager::gamePadButtonPress(Input _input)
{

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



void InputManager::readKeyboard()
{
	if (previous_key == Inputs::NONE)
		return;

	if (!input_mapper->checkAndClearJoypadButton(previous_key))
	{
		previous_key = Inputs::NONE;
		return;
	}

	return;
}



void InputManager::readMouse()
{
}



void InputManager::update()
{
	readKeyboard();
}

#pragma endregion
