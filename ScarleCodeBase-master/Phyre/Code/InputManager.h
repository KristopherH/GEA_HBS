#pragma once
//C++

////PHYRE
//#include <Phyre.h>
//#include <Inputs/PhyreInputs.h>
//#include <Framework/PhyreFrameworkApplication.h>

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
};

namespace Phyre
{
	namespace PFramework
	{
		class PInputMapper;
	}
}
//class PInputMapper;

class InputManager
{
public:
	InputManager() = default;
	//InputManager(Phyre::PFramework::PInputMapper* _input_mapper);
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
#pragma endregion going to have to look more into this (pre-processor shit)

#pragma region Couple of checkers (need to double check what these would be)
	static bool init();
	static bool readKeyboard();
	static bool readMouse();
	static void update();
#pragma endregion

	static int mouse_x;
	static int mouse_y;
	static int mouse_x_translation;
	static int mouse_y_translation;

	//static Phyre::PFramework::PInputMapper* input_mapper;
private:
	//int convertCharToDinput(char _input)


};