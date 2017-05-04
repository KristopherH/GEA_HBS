#include "Platform.h"
#include <string>
#include "Texture.h"
#include "GameData.h"
#include "Button.h"
#include "Object_Factory.h"

std::map<std::string, Texture*> Platform::platform_sprites;

Platform::Platform(Sprite* sprite, std::string _name, std::string _tag)
	:EditableGameObject(sprite, _name, _tag)
{
	changeType(STANDARD);
}

void Platform::changeType(PLATFORM_TYPE type)
{
	platform_type = type;
	if (platform_type == END)
	{
		platform_type = STANDARD;
	}
	if (platform_type == FIRST)
	{
		platform_type = JUMP;
	}
	switch (platform_type)
	{
		case STANDARD:
			sprite->setTexture(platform_sprites["Standard"]);
			setTag("StandardPlatform");
			break;
		case SLOW:
			sprite->setTexture(platform_sprites["Slow"]);
			setTag("SlowPlatform");
			break;
		case STICKY:
			sprite->setTexture(platform_sprites["Sticky"]);
			setTag("StickyPlatform");
			break;
		case SPEED:
			sprite->setTexture(platform_sprites["Speed"]);
			setTag("SpeedPlatform");
			break;
		case CONVEYOR_LEFT:
			sprite->setTexture(platform_sprites["Conveyor"]);
			setTag("ConveyorLeft");
			conveyorPlatform(true);
			break;
		case CONVEYOR_RIGHT:
			sprite->setTexture(platform_sprites["Conveyor"]);
			setTag("ConveyorRight");
			conveyorPlatform(false);
			break;
		case JUMP:
			sprite->setTexture(platform_sprites["Jump"]);
			setTag("JumpPlatform");
			break;
	}	
	setSize(&size);
}

Platform * Platform::create(PLATFORM_TYPE type)
{
	Platform* platform = new Platform(new Sprite(platform_sprites["Standard"]), "Platform", "StandardPlatform");

	platform->changeType(type);
	return platform;
}

void Platform::init()
{
	Platform::platform_sprites["Standard"] = new Texture("StandardPlatform", GameData::renderer);
	Platform::platform_sprites["Standard"]->LoadPixelMap();
	Platform::platform_sprites["Speed"] = new Texture("SpeedPlatform", GameData::renderer);
	Platform::platform_sprites["Speed"]->LoadPixelMap();
	Platform::platform_sprites["Slow"] = new Texture("SlowPlatform", GameData::renderer);
	Platform::platform_sprites["Slow"]->LoadPixelMap();
	Platform::platform_sprites["Sticky"] = new Texture("StickyPlatform", GameData::renderer);
	Platform::platform_sprites["Sticky"]->LoadPixelMap();
	Platform::platform_sprites["Jump"] = new Texture("JumpPlatform", GameData::renderer);
	Platform::platform_sprites["Jump"]->LoadPixelMap();
	Platform::platform_sprites["Conveyor"] = new Texture("ConveyorPlatform", GameData::renderer);
	Platform::platform_sprites["Conveyor"]->LoadPixelMap();
}

void Platform::toggleEditing()
{
	EditableGameObject::toggleEditing();
	if (editing)
	{
		Button* platformType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]), "NameChanger", "NULL", this->tag);
		platformType->setSize(new Vec2(max(size.x, 100), 50));
		platformType->setPosition(new Vec2(position.x, position.y + size.y));
		platformType->setCallbackFunction([this, platformType]()
		{
			return;
		});
		platformType->setScreenSpace(false);
		ui_elements.push_back(platformType);

		Button* plusType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]), "NameChanger", "NULL", "");
		plusType->setSize(new Vec2(50, 50));
		plusType->setPosition(new Vec2(position.x + platformType->getSize().x, position.y + size.y));
		plusType->setCallbackFunction([this, platformType]()
		{
			nextType();
			platformType->setText(tag);
			return;
		});
		plusType->setScreenSpace(false);
		ui_elements.push_back(plusType);

		Button* minusType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]), "NameChanger", "NULL", "");
		minusType->setSize(new Vec2(50, 50));
		minusType->setPosition(new Vec2(position.x - minusType->getSize().x, position.y + size.y));
		minusType->setCallbackFunction([this, platformType]()
		{
			prevType();
			platformType->setText(tag);
			return;
		});
		minusType->setScreenSpace(false);
		ui_elements.push_back(minusType);

		/*std::string openBottomString = passThuBottom ? "Open Bottom" : "Closed Bottom";

		Button* openBottom = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", openBottomString);
		openBottom->setSize(new Vec2(100, 50));
		openBottom->setCallbackFunction([]()
		{
			return;
		});
		openBottom->setScreenSpace(false);
		ui_elements.push_back(openBottom);

		Button* plusOpenBottom = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		plusOpenBottom->setSize(new Vec2(50, 50));
		plusOpenBottom->setCallbackFunction([this, openBottom]()
		{
			passThuBottom = !passThuBottom;
			std::string openBottomString = passThuBottom ? "Open Bottom" : "Closed Bottom";
			openBottom->setText(openBottomString);
			return;
		});
		plusOpenBottom->setScreenSpace(false);
		ui_elements.push_back(plusOpenBottom);

		Button* minusOpenBottom = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minusOpenBottom->setSize(new Vec2(50, 50));

		minusOpenBottom->setCallbackFunction([this, openBottom]()
		{
			passThuBottom = !passThuBottom;
			std::string openBottomString = passThuBottom ? "Open Bottom" : "Closed Bottom";
			openBottom->setText(openBottomString);
			return;
		});
		minusOpenBottom->setScreenSpace(false);
		ui_elements.push_back(minusOpenBottom);


		minusOpenBottom->setPosition(new Vec2(position.x + size.x,
			position.y));
		openBottom->setPosition(new Vec2(position.x + size.x + minusOpenBottom->getSize().x,
			position.y));
		plusOpenBottom->setPosition(new Vec2(position.x + size.x + minusOpenBottom->getSize().x + openBottom->getSize().x,
			position.y));*/
	}

}

void Platform::nextType()
{
	int type = platform_type;
	type++;
	PLATFORM_TYPE pType = (PLATFORM_TYPE)(type);
	changeType(pType);
}

void Platform::prevType()
{
	int type = platform_type;
	type--;
	PLATFORM_TYPE pType = (PLATFORM_TYPE)(type);
	changeType(pType);
}

void Platform::conveyorPlatform(bool _left)
{
	setTag("ConveyorLeft");
	if (!_left)	setTag("ConveyorRight");
}