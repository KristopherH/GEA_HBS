#include "Platforms.h"

Platforms::Platforms()
{
}

GameObjectV2 * Platforms::standardPlatform(Renderer * _renderer, float x, float y, float sizeX, float sizeY, string name)
{
	spr = nullptr;
	platform = nullptr;

	spr = new Sprite("StandardPlatform", _renderer);
	platform = new GameObjectV2(spr, name, "Standard Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::stickyPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name)
{
	spr = nullptr;
	platform = nullptr;

	spr = new Sprite("StickyPlatform", _renderer);
	platform = new GameObjectV2(spr, name, "Sticky Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::speedPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name)
{
	spr = nullptr;
	platform = nullptr;

	spr = new Sprite("SpeedPlatform", _renderer);
	platform = new GameObjectV2(spr, name, "Speed Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::slowPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name)
{
	spr = nullptr;
	platform = nullptr;

	spr = new Sprite("SlowPlatform", _renderer);
	platform = new GameObjectV2(spr, name, "Slow Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::conveyorPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY, string name, bool _left)
{
	spr = nullptr;
	platform = nullptr;

	spr = new Sprite("ConveyorPlatform", _renderer);
	
	std::string tag = "Conveyor Left";
	if (!_left)	tag = "Conveyor Right";

	platform = new GameObjectV2(spr, name, tag);

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2 * Platforms::jumpPlatform(Renderer * _renderer, float x, float y, float sizeX, float sizeY, string name)
{
	spr = nullptr;
	platform = nullptr;

	spr = new Sprite("JumpPlatform", _renderer);
	platform = new GameObjectV2(spr, name, "Jump Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}
