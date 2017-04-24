#include "Button.h"
#include "GameData.h"
#include "Collision_Manager.h"
#include "Input_Manager.h"
#include "BaseCamera.h"


#include "DXTKRenderer.h"
#include "CustomMath.h"

Button::Button(Sprite* sprite, std::string _name, std::string _tag, string _text)
	:GameObject(sprite, _name, _tag)
{
	buttonText = _text;
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

	GameObject::Draw();

	GameData::renderer->renderText(buttonText, Vec2((getPosition().x - getSize().x) - 500.0f, (getPosition().y - getSize().y) - 280),
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f/*getPosition().x, getPosition().y*/), ((getSize().x + getSize().y) / 100) / 6);

	float newy;

	newy = (getPosition().y - getSize().y);
	
	return true;
}

void Button::setCallbackFunction(std::function<void()> funct)
{
	onClick = funct;
}

void Button::setColor(Vec4 colour)
{
}
