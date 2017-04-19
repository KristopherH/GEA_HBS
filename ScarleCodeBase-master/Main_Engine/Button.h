#pragma once
//c++
#include <functional>

//DXTK

//OURS
#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(Sprite* sprite, std::string _name, std::string _tag);

	virtual bool Update(float dt) override;
	virtual bool Draw() override;

	void setCallbackFunction(std::function<void()>);

	void setColor(Vec4 colour);

protected:
	std::function<void()> onClick;

	bool hovering = false;
};