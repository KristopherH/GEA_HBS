#include "Button.h"
#include "GameData.h"
#include "Collision_Manager.h"
#include "Input_Manager.h"
#include "BaseCamera.h"

Button::Button(Sprite* sprite, std::string _name, std::string _tag)
	:GameObject(sprite, _name, _tag)
{

}

bool Button::Update()
{
	GameObject::Update();
	sprite->setPosition(position - Vec2(GameData::currentCamera->getCameraSize().x /2,
										GameData::currentCamera->getCameraSize().y / 2));
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
