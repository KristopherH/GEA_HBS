#include "ballistics.h"
#include "Sprite.h"
#include "GameData.h"
#include "Player.h"

//Directon _D = Directon::D_NONE;

Ballistics::Ballistics()
	:GameObject(new Sprite("bullet", GameData::renderer), "Bullet", "Bullet")
{
	_BD = BulletDirecton::BD_Target;
	//sprite->setPosition(Vec2(0, 0));
}

Ballistics::~Ballistics()
{

}


bool Ballistics::Update(float dt)
{


	timer += dt;
	if (timer >= 30)
	{
		alive = false;
	}
	switch (_BD)
	{

	case BD_UP:

			acceleration -= Vec2(0, speed);
			setRotation(3.14f/2);
			break;

	case BD_DOWN:

			acceleration += Vec2(0, speed);
			setRotation(3.14f*1.5);
			break;

	case BD_RIGHT:


		    acceleration += Vec2(speed,0);
			setRotation(3.14f);
			break;

	case BD_LEFT:

			acceleration -= Vec2(speed, 0);

			break;

	case BD_Target:
		
			Vec2 BullDR = Vec2(GameData::player->getPosition().x, GameData::player->getPosition().y);
			BullDR -= position;
			BullDR.Normalize();
			BullDR.Limit(speed);
			velocity.x += BullDR.x;
			velocity.y += BullDR.y;
			rotation = atan2(-BullDR.x, BullDR.y);
			rotation -= 3.14 / 2;
			break;
	}
	GameObject::Update(dt);

	return true;
}

bool Ballistics::Draw()
{
	GameObject::Draw();
	return false;
}

