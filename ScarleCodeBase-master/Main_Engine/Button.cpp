#include "Button.h"
#include "GameData.h"
#include "Collision_Manager.h"
#include "Input_Manager.h"
#include "BaseCamera.h"


#include "DXTKRenderer.h"
#include "CustomMath.h"

Button::Button(Sprite* sprite, std::string _name, std::string _tag, string _text, bool _press)
	:GameObject(sprite, _name, _tag), press(_press)
{
	buttonText = _text;
	screenSpace = true;
}

Button::Button(Sprite* sprite, std::string _name, std::string _tag, char _text, bool _press)
	: GameObject(sprite, _name, _tag), press(_press)
{
	buttonText = _text;
	screenSpace = true;
}

bool Button::Update(float dt)
{
	GameObject::Update(dt);
	bool collision = false;
	if (screenSpace)
	{
		sprite->setScale((sprite->getScale() / GameData::currentCamera->getZoom()));
		sprite->setPosition(GameData::renderer->WorldToScreen(sprite->getPosition()));
		collision = box.Contains(Vec2((float)GameData::inputManager->mouse_x,
								(float)GameData::inputManager->mouse_y));
	}
	else
	{
		sprite->setPosition(position);
		collision = box.Contains(Vec2((float)GameData::inputManager->mouse_world_x,
								(float)GameData::inputManager->mouse_world_y));
	}
	if (collision)
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

	GameObject::Draw();
	GameData::renderer->renderText(buttonText, getSprite()->getPosition(),
		Vec4(0.3f, 0.7f, 0.2f, 1.0f), 0.0f,
		Vec2(0.0f, 0.0f),
		sprite->getSize() * sprite->getScale() /** 0.8f*/);
	
	return true;
}

void Button::setCallbackFunction(std::function<void()> funct)
{
	onClick = funct;
}

void Button::setColor(Vec4 colour)
{
}
