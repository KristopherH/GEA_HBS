#include "UI.h"

#include "GameData.h"
#include "Player.h"
#include "Texture.h"

UI::UI(Sprite * _sprite, BaseCamera * camera)
	: main_camera(camera)
{
}

UI::UI(std::vector<Sprite*> _sprites, BaseCamera * camera)
	: main_camera(camera)
{
}

UI::~UI()
{
}

bool UI::Update(float dt)
{
	return false;
}

bool UI::Draw()
{
	if (parallax)
	{
		for (unsigned int i = 0; i < UIElements.size(); i += 3)
		{
			Sprite* tmp = UIElements[i];
			GameData::renderer->Draw(UIElements[i]);
			GameData::renderer->Draw(UIElements[i + 1]);
			GameData::renderer->Draw(UIElements[i + 2]);
		}
	}
	else
	{
		GameData::renderer->Draw(sprite);
	}
	return false;
}
