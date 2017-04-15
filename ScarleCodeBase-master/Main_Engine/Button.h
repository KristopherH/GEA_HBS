#pragma once
//c++

//DXTK

//OURS
#include "GameObjectV2.h"

class Button : public GameObjectV2
{
public:
	Button(Sprite* sprite, std::string _name, std::string _tag);

	virtual bool Update() override;
	virtual bool Draw() override;

	void setCallbackFunction(std::function<void()>);

	void setColor(Vec4 colour);

protected:
	std::function<void()> onClick;

	bool hovering = false;
};