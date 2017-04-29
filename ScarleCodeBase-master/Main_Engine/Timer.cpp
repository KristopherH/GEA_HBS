#include "Timer.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Player.h"



Timer::Timer()
{

}

Timer::~Timer()
{

}

bool Timer::Update(float dt)	
{
	time += dt;
	GameObject::Update(dt);
	return true;

}

bool Timer::Draw()
{

	GameData::renderer->renderText("Timer " + std::to_string(Timer::getTime()), GameData::player->getPosition() + Vec2(620.0f, 220.0f),
		Vec4(0.0f, 0.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);

	//GameObject::Draw();
	return false;
}




