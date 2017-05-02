#include "Timer.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Player.h"

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
	setText("Elapsed Time: " + to_string(time));
	Text::Update(dt);
	return true;
}

bool Timer::Draw()
{
	Text::Draw();
	return false;
}




