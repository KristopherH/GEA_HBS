#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include "GameData.h"
#include "DXTKRenderer.h"
#include <Windows.h>

class TextBox : public GameObject
{
public:
	TextBox(Sprite* sprite, std::string _name, std::string _tag, std::string _text);
	~TextBox();

	bool Update(float dt) override;
	bool Draw() override;

private:
	std::string text;
	bool selected;
};