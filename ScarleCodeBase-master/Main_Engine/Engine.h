#pragma once
//C++
#include <vector>
#include <memory>
#include <list>
#include <map>
//External


//Internal
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include "GameDataV2.h"

using std::list;
using std::unique_ptr;

//Definitions
class GameObjectV2;
class Platforms;
class Text;
class PlayerV2;

class Engine
{
public:
	Engine(Renderer* _renderer, InputManager* _inputManager, 
			CollisionManager* _collision_manager, GameController* _game_controller);

	~Engine();

	bool Update();
	//void createCollectible(float x, float y);
	//void createCollectible(Renderer * _renderer, InputManager * _inputManager);
	bool Draw(); // will pass an object at the renderer and ask to draw it
	void clearGameObjectList();
	GameObjectV2* createLadder(float x, float y, float sizeX, float sizeY, bool solid, string name);
	GameObjectV2* createCollectible(float x, float y, float sizeX, float sizeY);
	void moveCamera(Vec2* _translation);
	void playGame();
	float m_dt;

private:
  
	Sprite* spd_plat;
	GameObjectV2* platform2;
	std::unique_ptr<Platforms> createPlatform;
	std::unique_ptr<Text> createText;
	Sprite* ladder_spr;
	GameObjectV2* ladder;
	Sprite* collectible_spr;
	GameObjectV2* collectible;
	PlayerV2* player;

protected:
	//GameDataV2* m_GD;
 
	BaseCamera* mainCamera = nullptr;
	BaseCamera* cam;
};