#include "UI.h"

#include "GameData.h"
#include "Player.h"
#include "Texture.h"

UI::UI(Sprite * _sprite, BaseCamera * camera)
	: main_camera(camera)
{
	sprite = _sprite;
	sprite->setPosition(main_camera->getPosition() * -1);
	Vec2 screenSize(GameData::screen.maxCorner);
	Vec2 scaleFactor(screenSize.x / sprite->getSize().x, screenSize.y / sprite->getSize().y);
	sprite->setScale(scaleFactor);
}

UI::UI(std::vector<Sprite*> UI_Sprites, BaseCamera * camera)
	: main_camera(camera)
{
	for (unsigned int i = 0; i < UI_Sprites.size(); i++)
	{
		UI_Sprites[i]->setOrigin(UI_Sprites[i]->GetTexture()->getSize() * 0.5f);
		UIElements.push_back(new Sprite(*UI_Sprites[i]));
	}

	for (unsigned int i = 0; i < UIElements.size(); i++)
	{
		Vec2 screenSize(GameData::screen.maxCorner);
		Vec2 scaleFactor(0.2f, 0.2f);
		
		UIElements[i]->setScale(scaleFactor);
	}
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
	UIElements[0]->setPosition(Vec2(GameData::player->getPosition().x + 700.0f, GameData::player->getPosition().y + 320));

	float x;
	float y;

	x = GameData::player->getPosition().x + 700.0f;
	y = GameData::player->getPosition().y + 320;

	for (unsigned int i = 0; i < UIElements.size(); i++)
	{
		GameData::renderer->Draw(UIElements[i]);	
	}
	
	return false;
}
