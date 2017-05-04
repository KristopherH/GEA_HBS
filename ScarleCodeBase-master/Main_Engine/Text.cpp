#include "Text.h"
#include "BaseCamera.h"

Text::Text(Sprite * sprite, std::string _name, std::string _tag, std::string _text)
	:GameObject(sprite, _name, _tag), color(Vec4(0.3f, 0.7f, 0.2f, 1.0f))
{
	text = _text;
	screenSpace = true;
	setType("Text");
}

Text::~Text()
{
}

bool Text::Update(float dt)
{
	GameObject::Update(dt);
	if (screenSpace)
	{
		if (sprite)
		{
			sprite->setScale((sprite->getScale() / GameData::currentCamera->getZoom()));
			sprite->setPosition(GameData::renderer->WorldToScreen(sprite->getPosition()));
		}
	}
	else
	{
		if (sprite)
		{
			sprite->setPosition(position);
		}
	}
	return true;
}

bool Text::Draw()
{
	GameObject::Draw();
	Vec2 pos;
	if (screenSpace)
	{
		pos += GameData::renderer->WorldToScreen(position);
	}
	else
	{
		pos += position;
	}
	GameData::renderer->renderText(text, pos,
		color, 0.0f,
		Vec2(0.0f, 0.0f),
		size);
	return true;
}

void Text::setScreenSpace(bool _screenSpace)
{
	screenSpace = _screenSpace;
}

std::string Text::getText()
{
	return text;
}

void Text::setText(std::string _text)
{
	text = _text;
}

void Text::setColor(Vec4 _color)
{
	color.x = _color.x;
	color.y = _color.y;
	color.z = _color.z;
	color.w = _color.w;
}
