#pragma once

class GameObject;

class ObjectManager
{
public:
	GameObject createGameObject();
	void deleteGameObject(GameObject& gameObject);

private:
};