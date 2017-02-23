#include "CustomMath.h"

//-----------------------
//-----Vec2
//-----------------------
#pragma region Vec2
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

#pragma endregion

//-----------------------
//-----Vec3
//-----------------------
#pragma region Vec3

Vec3::Vec3(float _x, float _y, float _z)
	:x(_x), y(_y), z(_z)
{
}

DirectX::SimpleMath::Vector3 Vec3::operator=(Vec3 _vec)
{
	return DirectX::SimpleMath::Vector3(_vec.x, _vec.y, _vec.z);
}

Vec3 Vec3::operator=(DirectX::SimpleMath::Vector3 _vec)
{
	return Vec3(_vec.x, _vec.y, _vec.z);
}

Vec3::operator DirectX::SimpleMath::Vector3()
{
	return DirectX::SimpleMath::Vector3(x, y, z);
}

/*Vec3 & Vec3::operator=(const Vec3 & other)
{
return Vec3(other.x, other.y, other.z);
}*/

Vec3& Vec3::operator+=(const Vec3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return (*this);
}

Vec3& Vec3::operator-=(const Vec3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return(*this);
}

Vec3& Vec3::operator*=(const Vec3 & oth)
{
	x = y*oth.z - z*oth.y;
	y = z*oth.x - x*oth.z;
	z = x*oth.y - y*oth.x;
	return (*this);
}

Vec3& Vec3::operator*=(const float & oth)
{
	x *= oth;
	y *= oth;
	z *= oth;
	return (*this);
}

Vec3& Vec3::operator/=(const float & oth)
{
	x /= oth;
	y /= oth;
	z /= oth;
	return (*this);
}

DirectX::SimpleMath::Vector3 Vec3::toDXTK(Vec3 oth)
{
	return DirectX::SimpleMath::Vector3(oth.x, oth.y, oth.z);
}

const Vec3 Vec3::Zero = Vec3(0.0f, 0.0f, 0.0f);
const Vec3 Vec3::Up = Vec3(0.0f, 1.0f, 0.0f);

void Vec3::Limit(float _length)
{
	float l2 = LenghtSqrd();
	if (l2 > _length*_length && l2 > 0)
	{
		float ratio = _length / (float)sqrt(l2);
		x *= ratio;
		y *= ratio;
		z *= ratio;
	}
}

void Vec3::Normalize()
{
	float l2 = LenghtSqrd();
	if (l2 > 0.0f || l2 < 0.0f)
	{
		float ratio = 1 / (float)sqrt(l2);
		x *= ratio;
		y *= ratio;
		z *= ratio;
	}
}

float Vec3::Length()
{
	return sqrt((x*x) + (y*y) + (z*z));
}

float Vec3::LenghtSqrd()
{
	return (x*x) + (y*y) + (z*z);
}

float Vec3::Distance(const Vec3 & V1, const Vec3 & V2)
{
	return sqrt((V1.x - V2.x)*(V1.x - V2.x) + (V1.y - V2.y)*(V1.y - V2.y) + (V1.z - V2.z)*(V1.z - V2.z));
}

float Vec3::DistanceSqrd(const Vec3 & V1, const Vec3 & V2)
{
	return (V1.x - V2.x)*(V1.x - V2.x) + (V1.y - V2.y)*(V1.y - V2.y) + (V1.z - V2.z)*(V1.z - V2.z);
}

Vec3 operator+(const Vec3 & V1, const Vec3 & V2)
{
	return Vec3(V1.x + V2.x, V1.y + V2.y, V1.z + V2.z);
}

Vec3 operator-(const Vec3 & V1, const Vec3 & V2)
{
	return Vec3(V1.x - V2.x, V1.y - V2.y, V1.z - V2.z);
}


#pragma endregion

//-----------------------
//-----Vec4
//-----------------------
#pragma region Vec4
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
	return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

#pragma endregion

//-----------------------
//-----Rect
//-----------------------
#pragma region Rect

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

#pragma endregion

//-----------------------
//-----SimpleMatrix
//-----------------------
#pragma region Matrix

OurMatrix::OurMatrix(float m00, float m01, float m02, float m03, 
					float m10, float m11, float m12, float m13, 
					float m20, float m21, float m22, float m23, 
					float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;

	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

OurMatrix::OurMatrix(const float * pArray)
{
	assert(pArray != nullptr);

	m[0][0] = pArray[0];
	m[0][1] = pArray[1];
	m[0][2] = pArray[2];
	m[0][3] = pArray[3];

	m[1][0] = pArray[4];
	m[1][1] = pArray[5];
	m[1][2] = pArray[6];
	m[1][3] = pArray[7];

	m[2][0] = pArray[8];
	m[2][1] = pArray[9];
	m[2][2] = pArray[10];
	m[2][3] = pArray[11];

	m[3][0] = pArray[12];
	m[3][1] = pArray[13];
	m[3][2] = pArray[14];
	m[3][3] = pArray[15];
}

OurMatrix OurMatrix::CreatePerspectiveFieldOfView(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance)
{
	return toOur(DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance));
}

OurMatrix OurMatrix::CreateLookAt(Vec3 position, Vec3 m_target, Vec3 m_up)
{
	DirectX::SimpleMath::Vector3 pos = Vec3::toDXTK(position);
	DirectX::SimpleMath::Vector3 targ = Vec3::toDXTK(m_target);
	DirectX::SimpleMath::Vector3 up = Vec3::toDXTK(m_up);
	return toOur(DirectX::SimpleMath::Matrix::CreateLookAt(pos, DirectX::SimpleMath::Vector3::Forward, DirectX::SimpleMath::Vector3::Up));
}

OurMatrix OurMatrix::CreateTrasform(Vec3 _pos)
{
	return toOur(DirectX::SimpleMath::Matrix::CreateTranslation(_pos));
}

#pragma endregion