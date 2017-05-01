#include "GameOver.h"
//C++

//DXTK

//OURS
#include "GameData.h"
#include "Player.h"







GameOver::GameOver()
{

}

void GameOver::Update(float dt)
{

}

void GameOver::Draw()
{

	if (GameData::player->getLives() <= 0)
	{

		GameData::renderer->renderText("Your Score: " + std::to_string(GameData::player->getScore()), Vec2(0.0f, 0.0f),
			Vec4(0.0f, 0.0f, 250.0f, 1.0f), 0.0f, Vec2(0.0f, 0.0f), 0.7f);
		std::vector<Sprite*> GameOver;
		GameOver.push_back(new Sprite("GameOverBackGround", GameData::renderer));


	}
	
}


