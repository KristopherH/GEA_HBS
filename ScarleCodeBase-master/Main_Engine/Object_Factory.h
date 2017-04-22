#pragma once

class GameObject;

class ObjectFactory
{
public:
	static GameObject* createPlayer();
	static GameObject* createEnemy();
	static GameObject* createPlatform();
	static GameObject* createLadder();
	static GameObject* createCollectable();
	static GameObject* createBackground();

};