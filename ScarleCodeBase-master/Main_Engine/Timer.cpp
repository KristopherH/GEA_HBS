#include "Timer.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Player.h"
#include "Helper.h"

Timer::Timer()
	:Text(nullptr, "", "", "")
{
	setType("Timer");
}

Timer::~Timer()
{

}

bool Timer::Update(float dt)	
{
	time += dt;
	setText("Elapsed Time: " + Helper::to_string_with_precision((int)time, 4));
	Text::Update(dt);
	return true;
}

bool Timer::Draw()
{
	Text::Draw();
	return false;
}




