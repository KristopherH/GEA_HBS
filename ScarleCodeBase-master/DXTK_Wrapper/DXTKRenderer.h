#pragma once

class GameObject;

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Draw(GameObject* _go);
private:

};
