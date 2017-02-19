#include "CustomMath.h"

Vec2::Vec2(float _x, float _y)
	:x(_x), y(_y)
{
}

DirectX::SimpleMath::Vector2 Vec2::operator=(Vec2)
{
	return DirectX::SimpleMath::Vector2();
}

Vec2 Vec2::operator=(DirectX::SimpleMath::Vector2 _vec)
{
	return Vec2(_vec.x, _vec.y);
}

Vec2 & Vec2::operator*=(const float & other)
{
	x *= other;
	y *= other;
	return *this;
}


void Vec2::Limit(float _length)
{
	if (LengthSqrd() > _length*_length)
	{
		float ratio = _length / Length();
		x = x * ratio;
		y = y * ratio;
	}
}

void Vec2::Normalize()
{
	float ratio = 1 / Length();
	x = x * ratio;
	y = y * ratio;
}

float Vec2::Length()
{
	return sqrt(x*x + y*y);
}

float Vec2::LengthSqrd()
{
	return x*x + y*y;
}

float Vec2::Distance(const Vec2 & V1, const Vec2 & V2)
{
	return sqrt(((V1.x-V2.x)*(V1.x - V2.x))+((V1.y-V2.y)*(V1.y-V2.y)));
}

float Vec2::DistanceSqrd(const Vec2 & V1, const Vec2 & V2)
{
	return ((V1.x - V2.x)*(V1.x - V2.x)) + ((V1.y - V2.y)*(V1.y - V2.y));
}

Rect::Rect(Vec2, Vec2) 
{}

bool Rect::Contains(Vec2 oth)
{
	return false;
}

Vec2 Rect::Center()
{
	return Vec2();
}

Vec4::Vec4(float _x, float _y, float _z, float _w)
	:x(_x), y(_y), z(_z), w(_w)
{

}

DirectX::SimpleMath::Color Vec4::operator=(Vec4 oth)
{
	return DirectX::SimpleMath::Color(oth.x, oth.y, oth.z, oth.w);
}

Vec4 Vec4::operator=(DirectX::SimpleMath::Vector4 oth)
{
	return Vec4(oth.x, oth.y, oth.z, oth.w);
}

Vec4::operator DirectX::SimpleMath::Vector4()
{
	return Vec4();
}
