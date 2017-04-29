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
	newPos -= (GameData::currentCamera->getCameraSize() / 2) / GameData::currentCamera->getZoom();
	newPos -= GameData::currentCamera->getPosition();
	newPos += sprite->getPosition() / GameData::currentCamera->getZoom();
	sprite->setScale((sprite->getScale() / GameData::currentCamera->getZoom()));
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
	
	//return GameObject::Update(dt);
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

		/*GameData::renderer->renderText(buttonText, Vec2(((getSprite()->getPosition().x) - (getSprite()->getSize().x * 2)) - (getSprite()->getSize().x * 0.66),
			((getSprite()->getPosition().y / 2) - (getSprite()->getSize().y * 0.33))),
			Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f, 
			Vec2(0.0f, 0.0f),
			((getSize().x / 2) / (buttonText.size() / 2)) / 40);*/

	GameData::renderer->renderText(buttonText, Vec2(getSprite()->getPosition().x + 10, getSprite()->getPosition().y + 30),
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f,
		Vec2(0.0f, 0.0f),
		((getSize().x / 2) / (buttonText.size() / 2)) / 40);

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
