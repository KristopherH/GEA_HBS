#include "Platforms.h"

Platforms::Platforms()
{

}

void Platforms::stickyPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	stk_plat = new Sprite("StickyPlatform", _renderer);
	platform1 = new GameObjectV2(stk_plat, "Sticky Platform", "Sticky Platform");

	platform1->SetPosition(new Vec2(x, y));
	platform1->SetSize(new Vec2(sizeX, sizeY));
}

void Platforms::speedPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	spd_plat = new Sprite("SpeedPlatform", _renderer);
	platform2 = new GameObjectV2(spd_plat, "Speed Platform", "Speed Platform");

	platform2->SetPosition(new Vec2(x, y));
	platform2->SetSize(new Vec2(sizeX, sizeY));
}

void Platforms::slowPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	slw_plat = new Sprite("SlowPlatform", _renderer);
	platform3 = new GameObjectV2(slw_plat, "Slow Platform", "Slow Platform");

	platform3->SetPosition(new Vec2(x, y));
	platform3->SetSize(new Vec2(sizeX, sizeY));
}

void Platforms::conveyorPlatform(Renderer* _renderer, float x, float y, float sizeX, float sizeY)
{
	cnvyr_plat = new Sprite("ConveyorPlatform", _renderer);
	platform4 = new GameObjectV2(cnvyr_plat, "Conveyor Platform", "Conveyor Platform");

	platform4->SetPosition(new Vec2(x, y));
	platform4->SetSize(new Vec2(sizeX, sizeY));
}