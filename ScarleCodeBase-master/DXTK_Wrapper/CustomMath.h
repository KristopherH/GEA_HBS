#pragma once
//C++

//External
#include <d3d11_1.h>
#include "../Inc/SimpleMath.h"

//Internal

//Definitions

struct Vec2
{
	float x;
	float y;

	//Creation and convertion
	Vec2(float _x = 0.0f, float _y = 0.0f);
	DirectX::SimpleMath::Vector2 operator=(Vec2);
	Vec2 operator=(DirectX::SimpleMath::Vector2);
	operator DirectX::SimpleMath::Vector2() const { return  DirectX::SimpleMath::Vector2(x, y); }

	// Operator Overloads
	Vec2& operator+=(const Vec2& other) { return Vec2(x += other.x, y += other.y); }
	Vec2& operator-=(const Vec2& other);
	Vec2& operator*=(const Vec2& other);
	Vec2& operator*=(const float& other);
	Vec2& operator/=(const float& other);

	// Static Operators
	friend Vec2 operator+(const Vec2& V1, const Vec2& V2) { return Vec2(V1.x + V2.x, V1.y + V2.y); }
	friend Vec2 operator-(const Vec2& V1, const Vec2& V2) { return Vec2(V1.x - V2.x, V1.y - V2.y); }
	friend Vec2 operator*(const Vec2& V1, const float& V2) { return Vec2(V1.x * V2, V1.y * V2); }

	// Useful Functions
	void Limit(float _length);
	void Normalize();
	float Length();
	float LengthSqrd();
	static float Distance(const Vec2& V1, const Vec2& V2);
	static float DistanceSqrd(const Vec2& V1, const Vec2& V2);
};

struct Rect
{
	Vec2 min;
	Vec2 max;

	Rect(Vec2, Vec2);

	bool Contains(Vec2 oth);
	Vec2 Center();
};

struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	Vec4(float _x = 0.0f, float _y = 0.0f,float _z = 0.0f, float _w = 0.0f);
	DirectX::SimpleMath::Color operator=(Vec4);
	Vec4 operator=(DirectX::SimpleMath::Vector4);
	operator DirectX::SimpleMath::Vector4();
};