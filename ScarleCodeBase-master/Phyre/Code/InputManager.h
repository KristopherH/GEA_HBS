#pragma once

#include <Phyre.h>
#include <Inputs/PhyreInputs.h>

namespace Phyre
{
	namespace PFramework
	{
		class PInputMapper;
	}
}

using Input = Phyre::PInputs::PInputBase::PInputChannel;


struct Inputs
{
	static Input NONE;
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
	InputManager() = default;
	~InputManager() = default;

	#pragma region Mouse Input
	static bool getMouseRight();
	static bool getMouseLeft();
	static bool getMouseMiddle();
	#pragma endregion

	#pragma region Keyboard Input
	static bool getKeyDown(Input _key);
	static bool getKeyUp(Input _key);
	static bool getKeyHeld(Input _key);
	#pragma endregion

	#pragma region GamePad Input
	static bool gamePadButtonPress(Input _input);
	static bool gamePadButtonUp(Input _input);
	static bool gamePadButtonHeld(Input _input);
	#pragma endregion 

	#pragma region Couple of checkers (need to double check what these would be)
	static bool init();
	static void readKeyboard();
	static void readMouse();
	static void update();
	#pragma endregion

	static int mouse_x;
	static int mouse_y;
	static int mouse_x_translation;
	static int mouse_y_translation;

	static Phyre::PFramework::PInputMapper* input_mapper;
private:
	static Input previous_key;
};