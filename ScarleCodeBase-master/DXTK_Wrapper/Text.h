#pragma once
#include <d3d11_1.h>
#include "DXTKRenderer.h"
#include "CustomMath.h"
#include "Font.h"
#include <string>
//=================================================================
//A Game Object 2D for displaying images
//image needs to have been converted to a dds by the Assets project
//add orginal file to this project and set it to "Image Content Pipeline"
// in a similar fashion as getting the models
//=================================================================

using namespace DirectX;
using namespace std;

class Text
{
public:
	Text(string* string);
	~Text() = default;

	string* GetString() { return m_string; }

private:
	string* m_string;
};