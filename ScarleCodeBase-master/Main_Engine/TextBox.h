#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include "GameData.h"
#include "DXTKRenderer.h"
#include <Windows.h>
#include <mutex>

class TextBox : public GameObject
{
public:
	TextBox(Sprite* sprite, std::string _name, std::string _tag, std::string _text);
	~TextBox();

	bool Update(float dt) override;
	bool Draw() override;

	void setOnEnterCallback(std::function<void()> funct);

	std::string getText();

private:
	std::mutex mtx;
	std::thread* handle;
	std::string text;
	bool selected;
	bool entered = true;

	std::function<void()> onEnter;
};