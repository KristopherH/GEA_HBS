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
}
Button::Button(Sprite* sprite, std::string _name, std::string _tag, char _text, bool _press)
	: GameObject(sprite, _name, _tag), press(_press)
{
	buttonText = _text;
}

bool Button::Update(float dt)
{
	GameObject::Update(dt);
	Vec2 newPos = Vec2(0.0f, 0.0f);
	newPos -= (GameData::currentCamera->getCameraSize() / 2) / GameData::currentCamera->getZoom();
	newPos -= GameData::currentCamera->getPosition();
	newPos += sprite->getPosition() / GameData::currentCamera->getZoom();
	sprite->setScale((sprite->getScale() / GameData::currentCamera->getZoom()));
	sprite->setPosition(newPos);

	if (box.Contains(Vec2((float)GameData::inputManager->mouse_x, (float)GameData::inputManager->mouse_y)))
	{
		hovering = true;
		if (press)
		{
			if (GameData::inputManager->getMouseLeftPress())
			{
				onClick();
			}
		}
		else
		{
			if (GameData::inputManager->getMouseLeft())
			{
				onClick();
			}
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

	GameData::renderer->renderText(buttonText, getSprite()->getPosition() /*+ ((sprite->getSize() * sprite->getScale()))*/,
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f,
		Vec2(0.0f, 0.0f),
		sprite->getSize() * sprite->getScale() /** 0.8f*/);

	float newy;
	float newx;

	newx = getSprite()->getPosition().x;
	newy = getSprite()->getPosition().y;
	
	return true;
}

void Button::setCallbackFunction(std::function<void()> funct)
{
	onClick = funct;
}

void Button::setColor(Vec4 colour)
{
}
