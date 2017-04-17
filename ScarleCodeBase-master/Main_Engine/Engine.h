#pragma once
//C++
#include <vector>
#include <memory>
#include <list>
#include <map>
//DXTK

//OURS
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "GameData.h"

using std::list;
using std::unique_ptr;

//Definitions
class GameObject;
class Platforms;
class Text;
class Player;

class Engine
{
public:
	Engine(Renderer* _renderer, InputManager* _inputManager, 
			CollisionManager* _collision_manager, GameController* _game_controller);

	~Engine();

	bool Update();
	bool Draw(); // will pass an object at the renderer and ask to draw it
	void clearGameObjectList();
	GameObject* createLadder(float x, float y, float sizeX, float sizeY, bool solid, string name);
	GameObject* createCollectible(float x, float y, float sizeX, float sizeY);
	void moveCamera(Vec2* _translation);
	void playGame();
	float m_dt;

private:
	Sprite* spd_plat;
	GameObject* platform2;
	std::unique_ptr<Platforms> createPlatform;
	std::unique_ptr<Text> createText;

protected: 
	BaseCamera* mainCamera = nullptr;
	BaseCamera* cam;
	string playerLives;
	int lives;
};