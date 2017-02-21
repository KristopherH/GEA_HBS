#include "PlayerLives.h"
#include "GameOver.h"

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

	 lives = -1;

	 /*
		checkpoint system 
		will get the players last check point position 
		then repawn them there 
	 
	 */

	}

	else if (lives == 0)

	{

		GameOver();

	}
	

};