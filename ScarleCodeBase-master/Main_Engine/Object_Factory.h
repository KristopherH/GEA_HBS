#pragma once

class GameObject;

class ObjectFactory
{
public:
	ObjectFactory() = default;
	~ObjectFactory() = default;

	GameObject* createPlayer();
	GameObject* createEnemy();
	GameObject* createPlatform();
	GameObject* createLadder();
	GameObject* createCollectable();
	GameObject* createBackground();

};