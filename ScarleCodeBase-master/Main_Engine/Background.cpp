#include "Background.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Player.h"
#include "Texture.h"

Background::Background(Sprite * _sprite, BaseCamera * camera)
	:main_camera(camera)
{
	sprite = _sprite;
	parallax = false;
	sprite->setPosition(main_camera->getPosition() * -1);
	Vec2 screenSize(GameData::screen.max);
	Vec2 scaleFactor(screenSize.x / sprite->getSize().x, screenSize.y / sprite->getSize().y);
	sprite->setScale(scaleFactor);
}

Background::Background(std::vector<Sprite*> _sprites, BaseCamera * camera)
	: main_camera(camera)
{
	for (unsigned int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->setOrigin(_sprites[i]->GetTexture()->getSize() * 0.5f);
		backgrounds.push_back(new Sprite(*_sprites[i]));
		backgrounds.push_back(new Sprite(*_sprites[i]));
		backgrounds.push_back(new Sprite(*_sprites[i]));
		
	}
	for (unsigned int i = 0; i < backgrounds.size(); i+=3)
	{
		Vec2 screenSize(GameData::screen.max);
		Vec2 scaleFactor(2, 2);/*screenSize.x / backgrounds[i]->getSize().x,
						 screenSize.y / backgrounds[i]->getSize().y);*/
		backgrounds[i]->setScale(scaleFactor /* (backgrounds.size() - i)*/);
		backgrounds[i + 1]->setScale(Vec2(scaleFactor.x, scaleFactor.y) /* (backgrounds.size() - i)*/);
		backgrounds[i + 2]->setScale(Vec2(scaleFactor.x, scaleFactor.y) /* (backgrounds.size() - i)*/);

		Vec2 centerPosition;
		centerPosition += GameData::player->getPosition();
		backgrounds[i]->setPosition(centerPosition);
		backgrounds[i+1]->setPosition(Vec2(centerPosition.x - (backgrounds[i]->getSize().x * backgrounds[i]->getScale().x), centerPosition.y));
		backgrounds[i+2]->setPosition(Vec2(centerPosition.x + (backgrounds[i]->getSize().x * backgrounds[i]->getScale().x), centerPosition.y));
		parallaxScales.push_back(-1.0f * i);
	}
	parallax = true;
	previousCamPosition += main_camera->getPosition() *-1;
}

Background::~Background()
{
}

bool Background::Update(float dt)
{
	if (parallax)
	{
		for (unsigned int i = 0; i < backgrounds.size(); i+=3)
		{
			float parallax = previousCamPosition.x - (main_camera->getPosition().x);
			Vec2 backgroundTargetPosition;
			backgroundTargetPosition += backgrounds[i]->getPosition();
			backgroundTargetPosition.x += parallax;
			Vec2 movement;
			movement += backgroundTargetPosition;
			movement -= backgrounds[i]->getPosition();
			movement.Limit(i/100.0f);
			backgrounds[i]->setPosition(backgrounds[i]->getPosition() + movement);
			backgrounds[i+1]->setPosition(backgrounds[i+1]->getPosition() + movement); 
			backgrounds[i+2]->setPosition(backgrounds[i+2]->getPosition() + movement);
		}
		previousCamPosition.x = 0.0f;
		previousCamPosition.y = 0.0f;
		previousCamPosition += main_camera->getPosition();
	}
	else
	{
		sprite->setPosition(main_camera->getPosition());
	}
	return false;
}

bool Background::Draw()
{
	if (parallax)
	{
		for (unsigned int i = 0; i < backgrounds.size(); i+=3)
		{
			Sprite* tmp = backgrounds[i];
			
			GameData::renderer->Draw(backgrounds[i]);
			GameData::renderer->Draw(backgrounds[i+1]);
			GameData::renderer->Draw(backgrounds[i+2]);
		}
	}
	else
	{
		GameData::renderer->Draw(sprite);
	}
	return false;
}
