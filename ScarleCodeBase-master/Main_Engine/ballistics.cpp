#include "ballistics.h"
#include "Sprite.h"
#include "GameData.h"
#include "Player.h"
#include "Collision_Manager.h"
>>>>>>> refs/remotes/origin/master

//Directon _D = Directon::D_NONE;

Ballistics::Ballistics(BulletDirecton _BD)
	:GameObject(new Sprite("bullet", GameData::renderer), "Bullet", "Bullet")
{
	BD = _BD;
	setScale(new Vec2(100, 100));
	setSolid(false);
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


	if (GameData::collsion_manager->boxCollision(box, GameData::player->getBox()))
	{
		GameData::player->killPlayer();
		alive = false; //Enemies don't die in the original game;
	}

	switch (BD)
	{

	case BD_UP:
			acceleration -= Vec2(0, bulletSpeed);
			setRotation(3.14f/2);
			break;

	case BD_DOWN:
			acceleration += Vec2(0, bulletSpeed);
			setRotation(3.14f*1.5f);
			break;
	case BD_RIGHT:
		    acceleration += Vec2(bulletSpeed,0);
			setRotation(3.14f);
			break;
	case BD_LEFT:
			acceleration -= Vec2(bulletSpeed, 0);
			break;
	case BD_Target:
			Vec2 BullDR = Vec2(GameData::player->getPosition().x, GameData::player->getPosition().y);
			BullDR -= position;
			BullDR.Normalize();
			BullDR.Limit(bulletSpeed);
			velocity.x += BullDR.x;
			velocity.y += BullDR.y;
			rotation = atan2(-BullDR.x, BullDR.y);
			rotation -= 3.14f / 2.0f;
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

