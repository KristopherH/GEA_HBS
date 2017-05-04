#include "Stairs.h"
#include "Button.h"
#include "Object_Factory.h"
#include "Helper.h"

Stairs::Stairs(Sprite* _sprite)
	:EditableGameObject(_sprite)
{
	setSize(new Vec2(100, 100));
	setType("Stairs");
}

Stairs::~Stairs()
{
}

bool Stairs::Update(float dt)
{
	return EditableGameObject::Update(dt);
}

bool Stairs::Draw()
{
	return EditableGameObject::Draw();
}

void Stairs::toggleEditing()
{
	EditableGameObject::toggleEditing();
	if (editing)
	{
		std::string side = left ? "Right Stair" : "Left Stair";
		Button* falltimerbtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", side);
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
			left = !left;
			if (left)
			{
				sprite->setTexture(ObjectFactory::texture_pool[STAIRS_LEFT]);
				falltimerbtn->setText("Left Stair");
			}
			else
			{
				sprite->setTexture(ObjectFactory::texture_pool[STAIRS_RIGHT]);
				falltimerbtn->setText("Right Stair");
			}
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
			left = !left;
			if (left)
			{
				sprite->setTexture(ObjectFactory::texture_pool[STAIRS_LEFT]);
				falltimerbtn->setText("Left Stair");
			}
			else
			{
				sprite->setTexture(ObjectFactory::texture_pool[STAIRS_RIGHT]);
				falltimerbtn->setText("Right Stair");
			}
			return;
		});
		minusFallTime->setScreenSpace(false);
		ui_elements.push_back(minusFallTime);
	}
}

void Stairs::setDirectionLeft(bool _left)
{
	if (left)
	{
		sprite->setTexture(ObjectFactory::texture_pool[STAIRS_LEFT]);
	}
	else
	{
		sprite->setTexture(ObjectFactory::texture_pool[STAIRS_RIGHT]);
	}
}
