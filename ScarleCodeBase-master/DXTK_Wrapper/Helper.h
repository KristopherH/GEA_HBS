#pragma once
//C++
#include <string>
#include <sstream>
#include <iomanip>

//DXTK

//OURS

//=================================================================
//helper function to convert to odd char type used by Microsoft stuff
//=================================================================

struct Helper
{
	static wchar_t* charToWChar(const char* _text)
	{
		size_t size = strlen(_text) + 1;
		static wchar_t* wa = NULL;
		if (wa)
		{
			delete[] wa;
			wa = NULL;
		}
		wa = new wchar_t[size];
		mbstowcs_s(nullptr, wa, size, _text, size);
		return wa;
	}

	template <typename T>
	static std::string to_string_with_precision(const T a_value, const int n = 6)
	{
		std::ostringstream out;
		out << std::setprecision(n) << a_value;
		return out.str();
	}
};