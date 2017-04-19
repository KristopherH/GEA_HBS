#pragma once
//C++

//PHYRE
#include <Phyre.h>
#include <Inputs/PhyreInputs.h>
#include <Framework/PhyreFrameworkApplication.h>

//OURS


using Input = int;
using namespace Phyre;
using namespace PFramework;
using namespace PRendering;
using namespace PGeometry;
using namespace PSerialization;
using namespace Vectormath::Aos;
using namespace PInputs;

struct Inputs
{
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
	InputManager() = delete;
	InputManager(PInputMapper* _input_mapper);
	~InputManager(); 

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

	static PInputMapper* input_mapper;
private:
	//int convertCharToDinput(char _input)


};