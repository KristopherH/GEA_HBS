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
	screenSpace = true;
}

TextBox::~TextBox()
{
	if (handle)
	{
		selected = false;
		handle->join();
		delete handle;
	}
}

bool TextBox::Update(float dt)
{
	GameObject::Update(dt);
	bool collision = false;
	if (screenSpace)
	{
		sprite->setScale((sprite->getScale() / GameData::currentCamera->getZoom()));
		sprite->setPosition(GameData::renderer->WorldToScreen(sprite->getPosition()));
		collision = box.Contains(Vec2((float)GameData::inputManager->mouse_x, (float)GameData::inputManager->mouse_y));
	}
	else
	{
		sprite->setPosition(position);
		collision = box.Contains(Vec2((float)GameData::inputManager->mouse_world_x, (float)GameData::inputManager->mouse_world_y));
	}
	if (collision)
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
		Vec4(0.3f, 0.7f, 0.2f, 1.0f), 0.0f,
		Vec2(0.0f, 0.0f),
		sprite->getSize() * sprite->getScale());
	mtx.unlock();
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
