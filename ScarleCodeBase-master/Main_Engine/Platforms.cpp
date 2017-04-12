#include "Platforms.h"

Platforms::Platforms(Renderer* _renderer)
{
	platform_sprites["Standard"] = new Sprite("StandardPlatform", _renderer);
	platform_sprites["Speed"] = new Sprite("SpeedPlatform", _renderer);
	platform_sprites["Slow"] = new Sprite("SlowPlatform", _renderer);
	platform_sprites["Sticky"] = new Sprite("StickyPlatform", _renderer);
	platform_sprites["Jump"] = new Sprite("JumpPlatform", _renderer);
	platform_sprites["Conveyor"] = new Sprite("ConveyorPlatform", _renderer);
}

GameObjectV2* Platforms::standardPlatform(float x, float y, float sizeX, float sizeY, string name)
{
	platform = new GameObjectV2(platform_sprites["Standard"], name, "Standard Platform");

	platform->setSize(new Vec2(sizeX, sizeY));
	platform->setPosition(new Vec2(x, y));

	return platform;
}

GameObjectV2* Platforms::stickyPlatform(float x, float y, float sizeX, float sizeY, string name)
{
	platform = new GameObjectV2(platform_sprites["Sticky"], name, "Sticky Platform");

	platform->setSize(new Vec2(sizeX, sizeY));
	platform->setPosition(new Vec2(x, y));
	
	return platform;
}

GameObjectV2* Platforms::speedPlatform(float x, float y, float sizeX, float sizeY, string name)
{
	platform = new GameObjectV2(platform_sprites["Speed"], name, "Speed Platform");

	platform->setSize(new Vec2(sizeX, sizeY));
	platform->setPosition(new Vec2(x, y));

	return platform;
}

GameObjectV2* Platforms::slowPlatform(float x, float y, float sizeX, float sizeY, string name)
{
	platform = new GameObjectV2(platform_sprites["Slow"], name, "Slow Platform");
	
	platform->setSize(new Vec2(sizeX, sizeY));
	platform->setPosition(new Vec2(x, y));

	return platform;
}

GameObjectV2* Platforms::conveyorPlatform(float x, float y, float sizeX, float sizeY, string name, bool _left)
{
	std::string tag = "Conveyor Left";
	if (!_left)	tag = "Conveyor Right";

	platform = new GameObjectV2(platform_sprites["Conveyor"], name, tag);

	platform->setSize(new Vec2(sizeX, sizeY));
	platform->setPosition(new Vec2(x, y));

	return platform;
}

GameObjectV2* Platforms::jumpPlatform(float x, float y, float sizeX, float sizeY, string name)
{
	platform = new GameObjectV2(platform_sprites["Jump"], name, "Jump Platform");

	platform->setSize(new Vec2(sizeX, sizeY));
	platform->setPosition(new Vec2(x, y));

	return platform;
}
