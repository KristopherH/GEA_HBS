#pragma once
//c++

//DXTK

//OURS
#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(Sprite* sprite, std::string _name, std::string _tag, std::string _text, bool _press = true);
	Button(Sprite * sprite, std::string _name, std::string _tag, char _text, bool _press = true);

	virtual bool Update(float dt) override;
	virtual bool Draw() override;

	void setCallbackFunction(std::function<void()>);

	void setColor(Vec4 colour);

protected:
	std::function<void()> onClick;

	bool hovering = false;
	float x;
	float y;
	std::string buttonText;
	bool press;
};