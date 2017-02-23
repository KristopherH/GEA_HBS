#include "BaseCamera.h"

BaseCamera::BaseCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vec3 _up, Vec3 _target)
{
	m_fieldOfView = _fieldOfView;
	m_aspectRatio = _aspectRatio;
	m_nearPlaneDistance = _nearPlaneDistance;
	m_farPlaneDistance = _farPlaneDistance;

	m_target = _target;
	m_up = _up;

	Vec3 pos3d(position.x, position.y);

	m_projMat = OurMatrix::CreatePerspectiveFieldOfView(m_fieldOfView, m_aspectRatio, m_nearPlaneDistance, m_farPlaneDistance);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	//m_rotMat = Matrix::CreateFromYawPitchRoll(m_yaw, m_pitch, m_roll); //possible not the best way of doing this!
	OurMatrix  transMat = OurMatrix::CreateTrasform(pos3d);

	m_worldMat = transMat;
}

BaseCamera::~BaseCamera()
{
}

bool BaseCamera::Update()
{
	position.x += -0.1f;
	Vec3 pos3d(position.x, position.y);

	m_projMat = OurMatrix::CreatePerspectiveFieldOfView(m_fieldOfView, m_aspectRatio, m_nearPlaneDistance, m_farPlaneDistance);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	//m_rotMat = Matrix::CreateFromYawPitchRoll(m_yaw, m_pitch, m_roll); //possible not the best way of doing this!
	OurMatrix  transMat = OurMatrix::CreateTrasform(pos3d);

	m_worldMat = transMat;
	return false;
}

bool BaseCamera::Draw()
{
	//DO NOTHING FOR NOW
	return false;
}


