#include "ballistics.h"
#include "Sprite.h"
#include "GameData.h"

//Directon _D = Directon::D_NONE;

Ballistics::Ballistics()
	:GameObject(new Sprite("bullet", GameData::renderer), "Bullet", "Bullet")
{
	_BD = BulletDirecton::BD_UP;
	//sprite->setPosition(Vec2(0, 0));
}

Ballistics::~Ballistics()
{

}


bool Ballistics::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;
	if (timer >= 20)
	{
		alive = false;
	}
	switch (_BD)
	{

	case BD_UP:

			acceleration -= Vec2(0, speed);
			break;

	case BD_DOWN:

			acceleration += Vec2(0, speed);
			break;
	case BD_RIGHT:

		    acceleration -= Vec2(speed,0);
			break;
	case BD_LEFT:

			acceleration += Vec2(speed, 0);
			break;
	case BD_Target:

		   // acceleration += Vec2(0, 1);
			break;
	
	}

	return true;
}

bool Ballistics::Draw()
{
	GameObject::Draw();
	return false;
}

