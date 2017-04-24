#include "Platform.h"
#include <string>
#include "Texture.h"
#include "GameData.h"

std::map<std::string, Texture*> Platform::platform_sprites;

Platform::Platform(Sprite* sprite, std::string _name, std::string _tag)
	:GameObject(sprite, _name, _tag)
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
	Platform::platform_sprites["Speed"] = new Texture("SpeedPlatform", GameData::renderer);
	Platform::platform_sprites["Slow"] = new Texture("SlowPlatform", GameData::renderer);
	Platform::platform_sprites["Sticky"] = new Texture("StickyPlatform", GameData::renderer);
	Platform::platform_sprites["Jump"] = new Texture("JumpPlatform", GameData::renderer);
	Platform::platform_sprites["Conveyor"] = new Texture("ConveyorPlatform", GameData::renderer);
}

void Platform::conveyorPlatform(bool _left)
{
	setTag("Conveyor Left");
	if (!_left)	setTag("Conveyor Right");
}