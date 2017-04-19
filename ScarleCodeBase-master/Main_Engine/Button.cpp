#include "Button.h"
#include "GameData.h"
#include "Collision_Manager.h"
//DXTK
#if defined _DXTK_
#include "..\DXTK_Wrapper\InputManager.h"
#elif defined _PHYRE_
//Phyre
#include "../Phyre/Code/InputManager.h"
#endif
#include "BaseCamera.h"

Button::Button(Sprite* sprite, std::string _name, std::string _tag)
	:GameObject(sprite, _name, _tag)
{

}

bool Button::Update(float dt)
{
	GameObject::Update(dt);
	Vec2 newPos = Vec2(0.0f, 0.0f);
	newPos -= GameData::currentCamera->getCameraSize() / 2;
	newPos -= GameData::currentCamera->getPosition();
	newPos += sprite->getPosition();
	sprite->setPosition(newPos);
	if (box.Contains(Vec2((float)GameData::inputManager->mouse_x, (float)GameData::inputManager->mouse_y)))
	{
		hovering = true;
		if (GameData::inputManager->getMouseLeft())
		{
			onClick();
		}
	}
	else
	{
		hovering = false;
	}
	
	return true;
}

bool Button::Draw()
{
	if (hovering)
	{

	}
	else
	{

	}
	return GameObject::Draw();
}

void Button::setCallbackFunction(std::function<void()> funct)
{
	onClick = funct;
}

void Button::setColor(Vec4 colour)
{
}
