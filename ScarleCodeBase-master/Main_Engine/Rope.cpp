#include "Rope.h"
#include "Texture.h"
#include "Player.h"
#include <algorithm> //remove and remove_if

Rope::Rope(Vec2 _pos, Texture * _texture, int _numOfNodes, float _springConst, float _springLength, float _springFrictionConst, Vec2 _ropeSize, vector<GameObject*>* go_list)
	:numOfNodes(_numOfNodes), springConst(_springConst), springLength(_springLength), springFrictionConst(_springFrictionConst), ropeSize(_ropeSize)
{
	type = "Rope";
	solid = false;
	Vec2 pos = _pos;
	position.x = _pos.x;
	position.y = _pos.y;
	RopeNode* rope0 = new RopeNode(new Sprite(_texture),
		_springConst, _springLength, _springFrictionConst);
	rope0->setSize(&ropeSize);
	rope0->setPosition(&pos);
	pos.y += ropeSize.y;
	ropeNodes.push_back(rope0);
	go_list->push_back(rope0);
	for (int i = 1; i < numOfNodes; i++)
	{
		RopeNode* rope1 = new RopeNode(new Sprite(_texture),
			springConst, springLength, springFrictionConst);
		rope1->setSize(&ropeSize);
		rope1->setPosition(&pos);
		pos.y += ropeSize.y;
		pos.x += 0.001f;
		ropeNodes.push_back(rope1);
		go_list->push_back(rope1);
		ropeNodes[i - 1]->setNextNode(rope1);
		ropeNodes[i]->setPrevNode(ropeNodes[i - 1]);
	}
	updateParenting();
}

Rope::~Rope()
{
}

bool Rope::Update(float dt)
{
	for (auto& rope : ropeNodes)
	{
		rope->gravityUpdate();
	}
	for (auto& rope : ropeNodes)
	{
		rope->Update(dt);
		rope->velocity += (((0-rope->velocity) * 0.00002f));
	}
	if (grabbedPlayer)
	{
		if (GameData::inputManager->getKeyDown(Inputs::JUMP))
		{
			grabbedPlayer = false;
			GameData::player->velocity.x = playerNode->velocity.x * 3;
			GameData::player->velocity.y = playerNode->velocity.y * 3;
			GameData::player->acceleration.x = 0;
			GameData::player->acceleration.y = 0;
		}
		else
		{
			if (GameData::inputManager->getKeyHeld(Inputs::UP))
			{
				playerPos.y -= 1.0f;
			}
			if (GameData::inputManager->getKeyHeld(Inputs::DOWN))
			{
				playerPos.y += 1.0f;
			}
			if (playerPos.y > 50.0f)
			{
				playerPos.y = 50.0f;
			}
			if (playerPos.y < -50.0f)
			{
				playerPos.y = -50.0f;
			}
			Vec2 pos;
			pos += playerNode->getPosition();
			pos += playerPos;
			GameData::player->setPosition(&pos);

			float maxDist = 10000.0f;
			for (auto& node : ropeNodes)
			{
				float dist = Vec2::DistanceSqrd(GameData::player->getPosition(), node->getPosition());
				if (maxDist >= dist)
				{
					maxDist = dist;
					playerNode = node;
					playerPos.x =  GameData::player->getPosition().x - node->getPosition().x;
					playerPos.y = GameData::player->getPosition().y - node->getPosition().y;
				}
			}

			if (playerNode != ropeNodes[0])
			{
				playerNode->velocity.x += GameData::player->velocity.x * 0.01f;
			}
		}
	}
	GameObject::Update(dt);
	return false;
}

bool Rope::Draw()
{
	for (auto& rope : ropeNodes)
	{
		rope->Draw();
	}
	return true;
}

void Rope::updateParenting()
{
	for (auto& node : ropeNodes)
	{
		node->setParent(this);
	}
}

void Rope::playerGrabbed(RopeNode* nodeGrabbed, Vec2 playerPosRelativeToNode)
{
	if (!grabbedPlayer && !(GameData::inputManager->getKeyHeld(Inputs::JUMP)))
	{
		grabbedPlayer = true;
		playerNode = nodeGrabbed;
		playerPos.x = playerPosRelativeToNode.x;
		playerPos.y = playerPosRelativeToNode.y;
	}
}

void Rope::addNode()
{
	RopeNode* rope1 = new RopeNode(new Sprite(ropeNodes[0]->getSprite()->GetTexture()),
		springConst, springLength, springFrictionConst);
	rope1->setSize(&ropeSize);
	Vec2 pos;
	pos += ropeNodes[ropeNodes.size() - 1]->getPosition();
	pos.y += ropeSize.y;
	rope1->setPosition(&pos);
	ropeNodes[ropeNodes.size() - 1]->setNextNode(rope1);
	rope1->setPrevNode(ropeNodes[ropeNodes.size() - 1]);
	ropeNodes.push_back(rope1);
	GameData::go_list->push_back(rope1);
	numOfNodes = ropeNodes.size();
	updateParenting();
}

void Rope::removeNode()
{
	if (ropeNodes.size() > 1)
	{
		GameData::go_list->erase(std::remove_if(GameData::go_list->begin(), GameData::go_list->end(), [this](GameObject* go)
		{
			return (go == ropeNodes[ropeNodes.size() - 1]);
		}), GameData::go_list->end());

		delete ropeNodes[ropeNodes.size() - 1];
		ropeNodes.erase(ropeNodes.end() - 1, ropeNodes.end());
		ropeNodes[ropeNodes.size() - 1]->setNextNode(nullptr);
	}
	numOfNodes = ropeNodes.size();
}

Vec2 Rope::getSize()
{
	return ropeNodes[0]->getSize();
}

Vec2 Rope::getScale()
{
	return ropeNodes[0]->getScale();
}

Vec2 Rope::getOrigin()
{
	return ropeNodes[0]->getOrigin();
}

float Rope::getRotation()
{
	return ropeNodes[0]->getRotation();
}

void Rope::setSize(Vec2 * _size)
{
	for (auto& node : ropeNodes)
	{
		node->setSize(_size);
	}
}

void Rope::setScale(Vec2 * _scale)
{
}

void Rope::setOrigin(Vec2 * _origin)
{
}

void Rope::setPosition(Vec2 * _pos)
{
	Vec2 translation;
	translation -= ropeNodes[0]->getPosition();
	translation += *_pos;
	movePosition(&translation);
	GameObject::setPosition(_pos);
}

void Rope::movePosition(Vec2 * _translation)
{
	for (auto node : ropeNodes)
	{
		node->setPosition(&(node->getPosition() + *_translation));
	}
	GameObject::movePosition(_translation);
}

Vec2 Rope::getPosition()
{
	return ropeNodes[0]->getPosition();
}

int Rope::getLength()
{
	return ropeNodes.size();
}