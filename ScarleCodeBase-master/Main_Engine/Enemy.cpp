#include "Enemy.h"
#include "GameDataV2.h"
#include "DXTKRenderer.h"
#include "Collision_Manager.h"
#include <vector>
#include <algorithm> // remove and remove_if
#include "Game_Controller.h"


Enemy::Enemy(Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
{
	SetSprite(new Sprite("enemy_sprite", GameDataV2::renderer));
	SetPosition(_pos);
	SetSize(_size);
	SetRotation(_rotation);
	setName(_name);
	setSolid(false);
}

Enemy::Enemy(Sprite * _sprite, Vec2* _pos, Vec2* _size, float _rotation, std::string _name)
	:GameObjectV2(_sprite)
{
	SetPosition(_pos);
	SetSize(_size);
	SetRotation(_rotation);
	setName(_name);
}

Enemy::~Enemy()
{
}

bool Enemy::Update()
{
	if (GameDataV2::collsion_manager->boxCollision(name, "Player"))
	{
 		player = new PlayerV2();
 		player->setLives();
		alive = false;
		//GameDataV2::go_list.erase(GameDataV2::go_list.begin() + GameDataV2::game_controller->getGameObjectLocation(name));
			
			
			/*std::remove_if(GameDataV2::go_list.begin(), GameDataV2::go_list.end(), 
			[](GameObjectV2* go) 
			{
				if (go->getName() == "Enemy1")
				{
					return true;
				}
				return false;
			}), GameDataV2::go_list.end());*/

	}
	return false;
}

