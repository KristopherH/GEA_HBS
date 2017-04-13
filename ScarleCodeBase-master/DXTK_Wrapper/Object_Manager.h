#pragma once
//C++

//DXTK

//OURS

class GameObject;

class ObjectManager
{
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	GameObject createGameObject();
	void deleteGameObject(GameObject& gameObject);

private:
};