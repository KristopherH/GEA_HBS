#include "gun.h"
#include "Sprite.h"
#include "GameData.h"
#include "Player.h"
#include "Button.h"
#include "Object_Factory.h"


Gun::Gun()
	:EditableGameObject(new Sprite("Cannon", GameData::renderer), "Cannon", "Cannon")
{
	setSize(new Vec2(100, 100));
	setType("Gun");
	directionNames[BD_Target] = "Hunt Player";
	directionNames[BD_UP] = "Up";
	directionNames[BD_DOWN] = "Down";
	directionNames[BD_LEFT] = "LEFT";
	directionNames[BD_RIGHT] = "RIGHT";
}

Gun::~Gun()
{

}


bool Gun::Update(float dt)
{
	timer += dt;
	if (timer >= ShootTime)
	{	
		Ballistics* bullet = new Ballistics(wanted_BD);
		bullet->setBulletSpeed(bulletSpeed);
	    GameData::go_list->push_back(bullet);
		bullet->setPosition(&position);
		bullet->setScale(&scale);
		timer = 0;
	}
	EditableGameObject::Update(dt);
	return true;
}

void Gun::toggleEditing()
{
	EditableGameObject::toggleEditing();
	if (editing)
	{
		//chnage bullet speed
		Button* speedBtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", "Speed:" + to_string(bulletSpeed));
		speedBtn->setSize(new Vec2(max(size.x, 100), 50));
		speedBtn->setPosition(new Vec2(position.x,
			position.y + size.y));
		speedBtn->setCallbackFunction([this, speedBtn]()
		{
			return;
		});
		speedBtn->setScreenSpace(false);
		ui_elements.push_back(speedBtn);

		Button* plusSpeed = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		plusSpeed->setSize(new Vec2(50, 50));
		plusSpeed->setPosition(new Vec2(position.x + speedBtn->getSize().x,
			position.y + size.y));
		plusSpeed->setCallbackFunction([this, speedBtn]()
		{
			bulletSpeed += 0.0002f;
			
			if (bulletSpeed <= 0.0002)
			{
				bulletSpeed = 0.0002;
			}
			speedBtn->setText("Speed:" + to_string(bulletSpeed));
			return;
		});
		plusSpeed->setScreenSpace(false);
		ui_elements.push_back(plusSpeed);

		Button* minusSpeed = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minusSpeed->setSize(new Vec2(50, 50));
		minusSpeed->setPosition(new Vec2(position.x - minusSpeed->getSize().x,
			position.y + size.y));
		minusSpeed->setCallbackFunction([this, speedBtn]()
		{
			bulletSpeed -= 0.0002f;
			
			if (bulletSpeed <= 0.0002)
			{
				bulletSpeed = 0.0002;
			}
			speedBtn->setText("Speed:" + to_string(bulletSpeed));
			return;
		});
		minusSpeed->setScreenSpace(false);
		ui_elements.push_back(minusSpeed);

		//change shoot time
		Button* timeBtn = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", "Rate of fire:" + to_string(ShootTime));
		timeBtn->setSize(new Vec2(max(size.x, 100), 50));
		timeBtn->setPosition(new Vec2(position.x,
			position.y + size.y + speedBtn->getSize().y));
		timeBtn->setCallbackFunction([this, timeBtn]()
		{
			return;
		});
		timeBtn->setScreenSpace(false);
		ui_elements.push_back(timeBtn);

		Button* plustime = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		plustime->setSize(new Vec2(50, 50));
		plustime->setPosition(new Vec2(position.x + timeBtn->getSize().x,
			position.y + size.y + speedBtn->getSize().y));
		plustime->setCallbackFunction([this, timeBtn]()
		{
			ShootTime += 1.0f;
			
			if (ShootTime <= 1.000)
			{
				ShootTime = 1.00;
			}
			timeBtn->setText("Rate of fire:" + to_string(ShootTime));
			return;
		});
		plustime->setScreenSpace(false);
		ui_elements.push_back(plustime);

		Button* minustime = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		minustime->setSize(new Vec2(50, 50));
		minustime->setPosition(new Vec2(position.x - minustime->getSize().x,
			position.y + size.y + speedBtn->getSize().y));
		minustime->setCallbackFunction([this, timeBtn]()
		{
			ShootTime -= 1.0f;
			
			return;

			if (ShootTime <= 1.000)
			{
				ShootTime = 1.00;
			}
			timeBtn->setText("Rate of fire:" + to_string(ShootTime));
		});
		minustime->setScreenSpace(false);
		ui_elements.push_back(minustime);

		//change bullet enum 
		Button* BullType = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON]),
			"NameChanger", "NULL", "Rate of fire:" + directionNames[wanted_BD]);
		BullType->setSize(new Vec2(max(size.x, 100), 50));
		BullType->setPosition(new Vec2(position.x,
			position.y + size.y + speedBtn->getSize().y + minustime->getSize().y));
		BullType->setCallbackFunction([this, BullType]()
		{
			return;
		});
		BullType->setScreenSpace(false);
		ui_elements.push_back(BullType);

		Button* BullTypeplus = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_PLUS]),
			"NameChanger", "NULL", "");
		BullTypeplus->setSize(new Vec2(50, 50));
		BullTypeplus->setPosition(new Vec2(position.x + BullType->getSize().x,
			position.y + size.y + speedBtn->getSize().y + minustime->getSize().y));
		BullTypeplus->setCallbackFunction([this, BullType]()
		{
			nextBulletDirection();
			BullType->setText("Bullet Type:" + directionNames[wanted_BD]);
			return;
		});
		BullTypeplus->setScreenSpace(false);
		ui_elements.push_back(BullTypeplus);

		Button* bullTypeMinus = new Button(new Sprite(ObjectFactory::texture_pool[BUTTON_MINUS]),
			"NameChanger", "NULL", "");
		bullTypeMinus->setSize(new Vec2(50, 50));
		bullTypeMinus->setPosition(new Vec2(position.x - bullTypeMinus->getSize().x,
			position.y + size.y + speedBtn->getSize().y + minustime->getSize().y));
		bullTypeMinus->setCallbackFunction([this, BullType]()
		{
			prevBulletDirection();
			BullType->setText("Bullet Type:" + directionNames[wanted_BD]);
			return;
		});
		bullTypeMinus->setScreenSpace(false);
		ui_elements.push_back(bullTypeMinus);
	}
}

void Gun::nextBulletDirection()
{
	int tmp = (int)wanted_BD;
	tmp++;
	wanted_BD = (BulletDirecton)tmp;
	if (wanted_BD == BD_END)
	{
		wanted_BD = BulletDirecton::BD_UP;
	}
}

void Gun::prevBulletDirection()
{
	int tmp = (int)wanted_BD;
	tmp--;
	wanted_BD = (BulletDirecton)tmp;
	if (wanted_BD == BD_START)
	{
		wanted_BD = BulletDirecton::BD_Target;
	}
}

bool Gun::Draw()
{
	EditableGameObject::Draw();
	return false;
}

