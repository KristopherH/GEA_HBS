#pragma once

struct Font
{
	Font(int _id, char* _name, int _size);

	int size = 0;           // font size
	char* description = "";  // name of font
	int id = 0;             // font id

	static Font* fonts[5]; // font array allows stored fonts
};