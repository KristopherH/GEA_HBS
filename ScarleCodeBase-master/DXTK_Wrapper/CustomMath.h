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

struct Vec3
{
	float x;
	float y;
	float z;

	//Creation and convertion
	Vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
	DirectX::SimpleMath::Vector3 operator=(Vec3);
	Vec3 operator=(DirectX::SimpleMath::Vector3);
	operator DirectX::SimpleMath::Vector3();


	//Operator Overloads
	//Vec3& operator=(const Vec3& other);
	Vec3& operator+=(const Vec3& otehr);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(const Vec3& other);
	Vec3& operator*=(const float& other);
	Vec3& operator/=(const float& other);

	static DirectX::SimpleMath::Vector3 toDXTK(Vec3);

	//Custom Vec3
	static const Vec3 Zero;
	static const Vec3 Up;

	void Limit(float _length);
	void Normalize();
	float Length();
	float LenghtSqrd();
	static float Distance(const Vec3& V1, const Vec3& V2);
	static float DistanceSqrd(const Vec3& V1, const Vec3& V2);
};

Vec3 operator+(const Vec3& V1, const Vec3& V2);
Vec3 operator-(const Vec3& V1, const Vec3& V2);

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

struct OurMatrix
{
	OurMatrix(	float m00 = 1.0f, float m01 = 0.0f, float m02 = 0.0f, float m03 = 0.0f, 
				float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, 
				float m20 = 0.0f, float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, 
				float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f);
	OurMatrix(_In_reads_(16) const float *pArray);

	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};

	float       operator() (size_t Row, size_t Column) const { return m[Row][Column]; }
	float&      operator() (size_t Row, size_t Column) { return m[Row][Column]; }

	static DirectX::SimpleMath::Matrix toDXTK(OurMatrix mat) { return DirectX::SimpleMath::Matrix(*mat.m); }
	static OurMatrix toOur(DirectX::SimpleMath::Matrix mat) { return OurMatrix(*mat.m); }

	static OurMatrix CreatePerspectiveFieldOfView(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance);
	static OurMatrix CreateLookAt(Vec3 position, Vec3 m_target, Vec3 m_up);
	static OurMatrix CreateTrasform(Vec3 _pos);
};