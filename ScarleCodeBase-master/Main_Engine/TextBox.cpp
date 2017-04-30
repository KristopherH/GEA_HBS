#include "TextBox.h"
#include "BaseCamera.h"
#include "Input_Manager.h"

TextBox::TextBox(Sprite* sprite, std::string _name, std::string _tag, std::string _text)
	:GameObject(sprite, _name, _tag)
{
	text = _text;
}

TextBox::~TextBox()
{
}

bool TextBox::Update(float dt)
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
		if (GameData::inputManager->getMouseLeftPress())
		{
			selected = true;
		}
	}
	else
	{
		if (GameData::inputManager->getMouseLeftPress())
		{
			selected = false;
		}
	}

	if (selected)
	{
		//char szInput[100];
		//for (int i = 0; i < text.length(); i++)
		//{
		//	szInput[i] = text.at(i);
		//}
		////TODO: change something to something better
		//CreateWindow(TEXT("Something"), szInput, WS_VISIBLE,
		//	10, 10, 100, 20, NULL, NULL, NULL, NULL);
		////text = szInput;
		//selected = false;
	}
	return true;
}

bool TextBox::Draw()
{
	GameObject::Draw();

	GameData::renderer->renderText(text, getSprite()->getPosition() /*+ ((sprite->getSize() * sprite->getScale()))*/,
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f,
		Vec2(0.0f, 0.0f),
		sprite->getSize() * sprite->getScale() /** 0.8f*/);

	float newy;
	float newx;

	newx = getSprite()->getPosition().x;
	newy = getSprite()->getPosition().y;

	return true;
}