#include "TextBox.h"
#include "BaseCamera.h"
#include "Input_Manager.h"
#include <future>
#include <sstream>
#include <string>

TextBox::TextBox(Sprite* sprite, std::string _name, std::string _tag, std::string _text)
	:GameObject(sprite, _name, _tag)
{
	text = _text;
}

TextBox::~TextBox()
{
	delete handle;
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
		if (GameData::inputManager->getMouseLeftPress() && !selected)
		{
			selected = true;
			handle = new std::thread([this]()
			{
				GameData::inputManager->startReading();
				char ch;
				do
				{
					ch = GameData::inputManager->getLatestInput();
					if (ch >= 0)
					{
						mtx.lock();
						if (text.size() < 30)
						{

							stringstream ss;
							string s;
							ss << ch;
							ss >> s;
							text.append(s);
						}
						mtx.unlock();
					}
					else if (ch == -1)
					{
						mtx.lock();
						if (text.size() > 0)
						{
							text.pop_back();
						}
						mtx.unlock();
					}
				} while (ch != -2 && selected);
				GameData::inputManager->stopReading();
				entered = false;
				selected = false;
				return;
			});
		}
	}
	else
	{
		if (GameData::inputManager->getMouseLeftPress() && selected)
		{
			selected = false;
			entered = false;
		}
	}

	if (!selected && !entered)
	{
		if (onEnter)
		{
			onEnter();
		}
		entered = true;
	}
	return true;
}

bool TextBox::Draw()
{
	GameObject::Draw();

	mtx.lock();
	GameData::renderer->renderText(text, getSprite()->getPosition(),
		Vec4(0.0f, 250.0f, 0.0f, 1.0f), 0.0f,
		Vec2(0.0f, 0.0f),
		sprite->getSize() * sprite->getScale());
	mtx.unlock();
	float newy;
	float newx;

	newx = getSprite()->getPosition().x;
	newy = getSprite()->getPosition().y;

	return true;
}

void TextBox::setOnEnterCallback(std::function<void()> funct)
{
	onEnter = funct;
}

std::string TextBox::getText()
{
	mtx.lock();
	std::string tmp = text;
	mtx.unlock();
	return tmp;
}
