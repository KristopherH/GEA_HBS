#ifndef _PLAYERLIVES_H_
#define _PLAYERLIVES_H_
#include "CMOGO.h"

//=================================================================
// Move to game over scene when lives gets to 0
//=================================================================

class PlayerLives 
{

public:

	PlayerLives();
	 ~PlayerLives();

	void lifeLost();

	int lives = 3;

};

#endif