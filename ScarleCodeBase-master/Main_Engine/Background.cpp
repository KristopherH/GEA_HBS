#include "Background.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Player.h"
#include "Texture.h"
#include "Collision_Manager.h"

Background::Background(Sprite * _sprite, BaseCamera * camera)
	:main_camera(camera)
{
	sprite = _sprite;
	parallax = false;
	sprite->setPosition(main_camera->getPosition() * -1);
	Vec2 screenSize(GameData::screen.maxCorner);
	Vec2 scaleFactor(screenSize.x / sprite->getSize().x, screenSize.y / sprite->getSize().y);
	sprite->setScale(scaleFactor);
}

Background::Background(std::vector<Sprite*> _sprites, BaseCamera * camera, Vec2* position)
	: main_camera(camera)
{
	type = "BG";
	for (unsigned int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->setOrigin(_sprites[i]->GetTexture()->getSize() * 0.5f);
		backgrounds.push_back(new Sprite(*_sprites[i]));
		backgrounds.push_back(new Sprite(*_sprites[i]));
		backgrounds.push_back(new Sprite(*_sprites[i]));
		
	}
	for (unsigned int i = 0; i < backgrounds.size(); i+=3)
	{
		Vec2 screenSize(GameData::screen.maxCorner);
		Vec2 scaleFactor(2, 2);
		backgrounds[i]->setScale(scaleFactor);
		backgrounds[i + 1]->setScale(scaleFactor);
		backgrounds[i + 2]->setScale(scaleFactor);

		Vec2 centerPosition;
		centerPosition += *position;
		backgrounds[i]->setPosition(Vec2(centerPosition.x - (backgrounds[i]->getSize().x * backgrounds[i]->getScale().x), centerPosition.y));
		backgrounds[i+1]->setPosition(centerPosition);
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
			movement.Limit(i/400.0f);
			backgrounds[i]->setPosition(backgrounds[i]->getPosition() + movement);
			backgrounds[i+1]->setPosition(backgrounds[i+1]->getPosition() + movement); 
			backgrounds[i+2]->setPosition(backgrounds[i+2]->getPosition() + movement);
		}
		previousCamPosition.x = 0.0f;
		previousCamPosition.y = 0.0f;
		previousCamPosition += main_camera->getPosition();
		if (GameData::player)
		{
			for (int i = 0; i < backgrounds.size(); i++)
			{
				Rect* box = new Rect(backgrounds[i]->getPosition(), backgrounds[i]->getPosition() + (backgrounds[i]->getSize() * backgrounds[i]->getScale()));
				*box = (*box + ((backgrounds[i]->getSize() * backgrounds[i]->getScale()) * -0.5f));
				if (GameData::collsion_manager->boxCollision(GameData::player->getBox(), *box))
				{
					if (i % 3 == 0)
					{
						backgrounds[i]->setPosition(Vec2(backgrounds[i]->getPosition().x - (backgrounds[i]->getSize().x * backgrounds[i]->getScale().x),
														 backgrounds[i]->getPosition().y));

						backgrounds[i + 1]->setPosition(Vec2(backgrounds[i+1]->getPosition().x - (backgrounds[i+1]->getSize().x* backgrounds[i]->getScale().x),
															 backgrounds[i+1]->getPosition().y));

						backgrounds[i + 2]->setPosition(Vec2(backgrounds[i+2]->getPosition().x - (backgrounds[i+2]->getSize().x* backgrounds[i]->getScale().x),
														 	 backgrounds[i+2]->getPosition().y));
					}
					else if (i % 3 == 1)
					{
						/*backgrounds[i - 1]->setPosition(Vec2(backgrounds[i]->getPosition().x - (backgrounds[i]->getSize().x),
															 backgrounds[i]->getPosition().y));

						backgrounds[i + 1]->setPosition(Vec2(backgrounds[i]->getPosition().x + (backgrounds[i]->getSize().x),
															 backgrounds[i]->getPosition().y));*/
					}
					else if (i % 3 == 2)
					{
						backgrounds[i]->setPosition(Vec2(backgrounds[i]->getPosition().x + (backgrounds[i]->getSize().x* backgrounds[i]->getScale().x),
							backgrounds[i]->getPosition().y));

						backgrounds[i - 1]->setPosition(Vec2(backgrounds[i - 1]->getPosition().x + (backgrounds[i - 1]->getSize().x* backgrounds[i]->getScale().x),
							backgrounds[i - 1]->getPosition().y));

						backgrounds[i - 2]->setPosition(Vec2(backgrounds[i - 2]->getPosition().x + (backgrounds[i - 2]->getSize().x* backgrounds[i]->getScale().x),
							backgrounds[i - 2]->getPosition().y));
					}
				}
				delete box;
			}
		}
		if (GameData::player)
		{	
			bool found = false;
			for (int i = 0; i < backgrounds.size(); i++)
			{
				Rect* box = new Rect(backgrounds[i]->getPosition(), backgrounds[i]->getPosition() + (backgrounds[i]->getSize() * backgrounds[i]->getScale()));
				*box = *box + (backgrounds[i]->getSize() * backgrounds[i]->getScale()) * -0.5f;
				if(GameData::collsion_manager->boxCollision(GameData::player->getBox(), *box))
				{
					found = true;
					break;
				}
				delete box;
			}
			if (!found)
			{
				
				GameData::player->killPlayer();
				for (unsigned int i = 0; i < backgrounds.size(); i += 3)
				{
					Vec2 centerPosition;
					centerPosition += GameData::player->getPosition();
					backgrounds[i]->setPosition(Vec2(centerPosition.x - (backgrounds[i]->getSize().x * backgrounds[i]->getScale().x), centerPosition.y));
					backgrounds[i + 1]->setPosition(centerPosition);
					backgrounds[i + 2]->setPosition(Vec2(centerPosition.x + (backgrounds[i]->getSize().x * backgrounds[i]->getScale().x), centerPosition.y));
				}
			}
		}
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
