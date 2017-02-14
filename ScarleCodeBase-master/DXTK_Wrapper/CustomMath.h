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
	operator DirectX::SimpleMath::Vector2();

	// Operator Overloads
	Vec2& operator+=(const Vec2& other) { this->x += other.x; this->y += other.y; }
	Vec2& operator-=(const Vec2& other) { this->x -= other.x; this->y -= other.y; }
	Vec2& operator*=(const Vec2& other) { this->x *= other.x; this->y *= other.y; }
	Vec2& operator*=(const float& other) { this->x *= other; this->y *= other; }
	Vec2& operator/=(const float& other) { this->x /= other; this->y /= other; }

	// Static Operators
	static Vec2 operator+(const Vec2& V1, const Vec2& V2); //{ x = V1.x + V2.x; y = V1.y + V2.y; }
	static Vec2 operator-(const Vec2& V1, const Vec2& V2);

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