#include "BaseCamera.h"
//C++

//DXTK

//OURS
#include "PlayerV2.h"

BaseCamera::BaseCamera(float _width, float _height, float _nearPlane, float _farPlane, Vec3 _up, Vec3 _target)
{
	width = _width;
	height = _height;
	nearPlane = _nearPlane;
	farPlane = _farPlane;
	position = Vec2(10.0f, 10.0f);
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

bool BaseCamera::Update()
{
	if (player)
	{
		setPosition(new Vec2(-player->getPosition().x, -player->getPosition().y));
		
		//setPlayerBoxPosX(player->GetPosition().x + player_box_width);
		//setPlayerBoxPosY(player->GetPosition().y + player_box_height);
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

	Vec3 pos3d(position.x, position.y);

	m_projMat = OurMatrix::CreateOrthographic(width, height, nearPlane, farPlane);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	m_worldMat = OurMatrix::CreateTrasform(pos3d, rotation, zoom, width, height);
	return false;
}

bool BaseCamera::Draw()
{
	//DO NOTHING FOR NOW
	return false;
}


