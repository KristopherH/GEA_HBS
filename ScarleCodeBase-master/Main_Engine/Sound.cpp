
#include "Sound.h"
#include <iostream>
#include <Audio.h>


Sound::Sound()
{

}


void Sound::Walking()
{
	PlaySound("..\\Assets\\Sounds\\Walking.wav", NULL, SND_LOOP | SND_ASYNC);
}

void Sound::Jumping()
{
	PlaySound("..\\Assets\\Sounds\\jump.wav", NULL, SND_ASYNC);
}

void Sound::BackGround()
{

}