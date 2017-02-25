#include "Font.h"

Font::Font(int _id, char * _desc, int _size)
	:id(_id), description(_desc), size(_size)
{

}

Font* Font::fonts[5] = { nullptr };