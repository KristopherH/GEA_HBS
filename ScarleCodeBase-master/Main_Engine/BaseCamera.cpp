#include "BaseCamera.h"
//C++

//DXTK

//OURS
#include "Player.h"

BaseCamera::BaseCamera(float _width, float _height, float _nearPlane, float _farPlane, Vec3 _up, Vec3 _target)
{
	width = _width;
	height = _height;
	viewWidth = _width;
	viewHeight = _height;
	nearPlane = _nearPlane;
	farPlane = _farPlane;
	position = Vec2(0.0f, 0.0f);
	m_target = _target;
	m_up = _up;

	Vec3 pos3d(position.x, position.y, 1.0f);

	m_projMat = OurMatrix::CreateOrthographic(width, height, nearPlane, farPlane);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	m_worldMat = OurMatrix::CreateTrasform(pos3d, rotation, zoom, width, height);
}

BaseCamera::~BaseCamera()
{
}

bool BaseCamera::Update(float dt)
{
	previousPosition.x = position.x;
	previousPosition.y = position.y;

	if (player)
	{
		if (Vec2::Distance(player->getPosition() * -1, position) > 10.0f)
		position += (Vec2(-player->getPosition().x, -player->getPosition().y) - position) * dt * 5;
	}

	/*Come back to this post alpha*/
	switch (movement_direction)
	{
	case Direction::TOP:
		//movePosition(new Vec2(0.0f, player->getSpeed()));
		break;
		
	case Direction::BOTTOM:
		//movePosition(new Vec2(0.0f, -player->getSpeed()));
		break;

	case Direction::LEFT:
		//movePosition(new Vec2(player->getSpeed(), 0.0f));
		break;

	case Direction::RIGHT:
		//movePosition(new Vec2(-player->getSpeed(), 0.0f));
		break;
	}
	zoom = 1.0f;
	Vec3 pos3d(position.x, position.y);

	m_projMat = OurMatrix::CreateOrthographic(width, height, nearPlane, farPlane);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	m_worldMat = OurMatrix::CreateTrasform(pos3d, rotation, zoom, width, height);
	return GameObject::Update(dt);
}

bool BaseCamera::Draw()
{
	//DO NOTHING FOR NOW
	return false;
}


