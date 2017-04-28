#include "RopeNode.h"
#include "GameData.h"
#include "Input_Manager.h"
#include "Collision_Manager.h"
#include "Player.h"
#include "Rope.h"

RopeNode::RopeNode(Sprite * sprite, std::string _name, std::string _tag)
	:GameObject(sprite, _name, _tag)
{
	solid = false;
	physics = false;
	origin += sprite->getSize();//around which rotation and scaing is done
	origin *= 0.5f;
	type = "RopeNode";
}

RopeNode::RopeNode(Sprite * _sprite, float _springConst, float _springLength, float _springFrictionConst)
	:GameObject(_sprite), springConst(_springConst), springFrictionConst(_springFrictionConst), springLength(_springLength)
{
	solid = false;
	physics = false;
	origin += _sprite->getSize();//around which rotation and scaing is done
	origin *= 0.5f;
	type = "RopeNode";
}

bool RopeNode::Update(float dt)
{
	if (nextNode)
	{
		Vec2 dir;
		dir -= position;
		dir += nextNode->getPosition();
		rotation = atan2(-dir.x, dir.y);
	}
	else
	{
		if (prevNode)
		{
			rotation = prevNode->getRotation();
		}
	}
	GameObject::Update(dt);
	velocity += acceleration * dt;
	position += velocity;
	acceleration.x = 0; 
	acceleration.y = 0;
	return false;
}

void RopeNode::gravityUpdate()
{
	if (!first)
	{
		Vec2 springVector = position - prevNode->getPosition();	//vector between the two masses

		float d = springVector.Length(); //distance between the two masses

		Vec2 force; //force initially has a zero value
		if (!first)
		{
			acceleration.y += 0.98f;
		}
		if (d != 0)
		{
			//force = -k * (x - d)
			//k: a constant to represent the stiffness of the spring
			//x : distance of the mass from the point it is bound to
			//d : a constant positive distance value that a spring stays steady
			force += (0-(springVector / d)) * (d - springLength) * springConst;	//the spring force is added to the force
		}
		force += (0-(velocity - prevNode->velocity)) * springFrictionConst;	//the friction force is added to the force
																//with this addition we obtain the net force of the sprin

		acceleration += force;	//force is applied to mass1
		if (!prevNode->first)
		{
			prevNode->acceleration -= force;//the opposite of force is applied to mass2
		}
	}

	for (auto& go : *GameData::go_list)
	{
		if (go->getAlive() && go->getSolid())
		{
			if (GameData::collsion_manager->boxCollision(box, go->getBox()))
			{
				if (go == (GameObject*)GameData::player)
				{
					parent->playerGrabbed(this, GameData::player->getPosition() - position);
					//GameData::player->velocity = velocity;
				}
				else
				{
					Vec2 centToSide;
					centToSide += box.Center();
					centToSide -= go->getBox().Center();
					if (Vec2::dot(centToSide, velocity) < 0.0f)
					{
						acceleration.x = 0.0f;
						acceleration.y = 0.0f;
						velocity.x = 0.0f;
						velocity.y = 0.0f;
					}
				}
			}
		}
	}
}

bool RopeNode::Draw()
{
	return GameObject::Draw();
}
