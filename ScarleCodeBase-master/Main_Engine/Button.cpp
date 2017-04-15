#include "Button.h"
#include "GameDataV2.h"
#include "Collision_Manager.h"
#include "Input_Manager.h"
#include "BaseCamera.h"

Button::Button(Sprite* sprite, std::string _name, std::string _tag)
	:GameObjectV2(sprite, _name, _tag)
{

}

bool Button::Update()
{
	GameObjectV2::Update();
	sprite->setPosition(position - Vec2(GameDataV2::currentCamera->getCameraSize().x /2,
										GameDataV2::currentCamera->getCameraSize().y / 2));
	if (box.Contains(Vec2(GameDataV2::inputManager->mouse_x, GameDataV2::inputManager->mouse_y)))
	{
		hovering = true;
		if (GameDataV2::inputManager->getMouseLeft())
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
	return GameObjectV2::Draw();
}

void Button::setCallbackFunction(std::function<void()> funct)
{
	onClick = funct;
}

void Button::setColor(Vec4 colour)
{
}
