#include "FallingPlatform.h"
#include "Sprite.h"
#include "GameData.h"
#include "Button.h"
#include "Object_Factory.h"
#include "Collision_Manager.h"
#include "Player.h"
#include "Helper.h"

FallingPlatform::FallingPlatform()
	:Platform(new Sprite("StandardPlatform", GameData::renderer), "StandardPlatform", "StandardPlatform")
{
	setSize(new Vec2(100, 100));
	setType("FallingPlatform");
}

FallingPlatform::~FallingPlatform()
{


}

bool FallingPlatform::Update(float dt)
{
	if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
	{
		isFalling = true;
	}

	if (isFalling == true)
	{
		fallTime += dt;
		if (fallTime >= toFallTime)
		{
			deadTime += dt;
			if (deadTime >= 2)
			{
				alive = false;
			}

			acceleration += Vec2(0, 0.1);

		}
	}

	Platform::Update(dt);

	return true;
}

bool FallingPlatform::Draw()
{
	Platform::Draw();
	return false;
}

void FallingPlatform::toggleEditing()
{
	Platform::toggleEditing();
	if (editing)
	{
		//chnage bullet speed
		Button* falltimerbtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", "Fall Time:" + Helper::to_string_with_precision(toFallTime));
		falltimerbtn->setSize(new Vec2(max(size.x, 100), 50));
		falltimerbtn->setPosition(new Vec2(position.x,
			position.y + size.y + falltimerbtn->getSize().y));
		falltimerbtn->setCallbackFunction([this, falltimerbtn]()
		{
			return;
		});
		falltimerbtn->setScreenSpace(false);
		ui_elements.push_back(falltimerbtn);

		Button* plusFallTime = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		plusFallTime->setSize(new Vec2(50, 50));
		plusFallTime->setPosition(new Vec2(position.x + falltimerbtn->getSize().x,
			position.y + size.y + falltimerbtn->getSize().y));
		plusFallTime->setCallbackFunction([this, falltimerbtn]()
		{
			toFallTime += 1.0f;
			
			if (toFallTime <= 1.0f)
			{
				toFallTime = 1.00;
			}
			falltimerbtn->setText("Fall Time:" + Helper::to_string_with_precision(toFallTime));
			return;
		});
		plusFallTime->setScreenSpace(false);
		ui_elements.push_back(plusFallTime);

		Button* minusFallTime = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minusFallTime->setSize(new Vec2(50, 50));
		minusFallTime->setPosition(new Vec2(position.x - minusFallTime->getSize().x,
			position.y + size.y + falltimerbtn->getSize().y));
		minusFallTime->setCallbackFunction([this, falltimerbtn]()
		{
			toFallTime -= 1.0f;
			
			if (toFallTime <= 1.0f)
			{
				toFallTime = 1.0f;
			}
			falltimerbtn->setText("Fall Time:" + Helper::to_string_with_precision(toFallTime));
			return;
		});
		minusFallTime->setScreenSpace(false);
		ui_elements.push_back(minusFallTime);
	}
}
