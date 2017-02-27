#include "Platforms.h"

Platforms::Platforms()
{

}

GameObjectV2 * Platforms::standardPlatform(Renderer * _renderer, float x, float y, float sizeX, float sizeY)
{
	spr = nullptr;
	platform = nullptr;
	spr = new Sprite("StickyPlatform", _renderer);
	platform = new GameObjectV2(spr, "Standard Platform", "Standard Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::stickyPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	spr = nullptr;
	platform = nullptr;
	spr = new Sprite("StickyPlatform", _renderer);
	platform = new GameObjectV2(spr, "Sticky Platform", "Sticky Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::speedPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	spr = nullptr;
	platform = nullptr;
	spr = new Sprite("SpeedPlatform", _renderer);
	platform = new GameObjectV2(spr, "Speed Platform", "Speed Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::slowPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	spr = nullptr;
	platform = nullptr;
	spr = new Sprite("SlowPlatform", _renderer);
	platform = new GameObjectV2(spr, "Slow Platform", "Slow Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2* Platforms::conveyorPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	spr = nullptr;
	platform = nullptr;
	spr = new Sprite("ConveyorPlatform", _renderer);
	platform = new GameObjectV2(spr, "Conveyor Platform", "Conveyor Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}

GameObjectV2 * Platforms::jumpPlatform(Renderer * _renderer, float x, float y, float sizeX, float sizeY)
{
	spr = nullptr;
	platform = nullptr;
	spr = new Sprite("StickyPlatform", _renderer);
	platform = new GameObjectV2(spr, "Jump Platform", "Jump Platform");

	platform->SetPosition(new Vec2(x, y));
	platform->SetSize(new Vec2(sizeX, sizeY));

	return platform;
}
