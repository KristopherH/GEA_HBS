#include "Button.h"
#include "GameData.h"
#include "Collision_Manager.h"
#include "Input_Manager.h"
#include "BaseCamera.h"


#include "DXTKRenderer.h"
#include "CustomMath.h"

Button::Button(Sprite* sprite, std::string _name, std::string _tag, string _text, Vec2 _position)
	:GameObject(sprite, _name, _tag)
{
	buttonText = _text;
	x = _position.x;
	y = _position.y;
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
	GameData::renderer->renderText(buttonText, Vec2(x, y),
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f, getOrigin(), 1.0f);

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
