#include "PlayerLives.h"
#include "GameState.h"
#include "GameData.h"

 PlayerLives::PlayerLives()
{



};

 PlayerLives::~PlayerLives()
{



};

void PlayerLives::lifeLost()
{
	if (lives != 0)

	{

	 lives --;

	 /*
		checkpoint system 
		will get the players last check point position 
		then repawn them there 
	 
	 */

	}

	else if (lives == 0)

	{

	 GameState::GS_GAME_OVER;

	}
	

};