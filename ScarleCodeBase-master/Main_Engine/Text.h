#pragma once
#include "GameObject.h"

class Text : public GameObject
{
public:
	Text(Sprite* sprite, std::string _name, std::string _tag, std::string _text);
	~Text();

	bool Update(float dt) override;
	bool Draw() override;

	void setScreenSpace(bool _screenSpace);

	std::string getText();
	void setText(std::string text);

	void setColor(Vec4 _color);

private:
	std::string text;
	bool screenSpace = true;
	Vec4 color;
};