#pragma once
#include  "..//Main_Engine/GameObjectV2.h"
#include "SpriteFont.h"
#include <string>
#include <memory>

using namespace std;

class Text : public GameObjectV2
{
public:
	Text() = default;
	~Text() = default;

	string createString(string text);
private:
	string newText = nullptr;
};
