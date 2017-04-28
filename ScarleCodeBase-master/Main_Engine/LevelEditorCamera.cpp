#include "LevelEditorCamera.h"

LevelEditorCamera::LevelEditorCamera(float _width, float _height, float _nearPlane, float _farPlane, Vec3 _up, Vec3 _target)
	:BaseCamera(_width, _height, _nearPlane, _farPlane)
{
	viewWidth = _width;
	viewHeight = _height;
}

LevelEditorCamera::~LevelEditorCamera()
{
}

bool LevelEditorCamera::Update(float dt)
{
	previousPosition.x = position.x;
	previousPosition.y = position.y;

	if (GameData::inputManager->getKeyHeld(Inputs::UP))
	{
		position += Vec2(0.0f, 2.0f);
	}
	if (GameData::inputManager->getKeyHeld(Inputs::DOWN))
	{
		position += Vec2(0.0f, -2.0f);

	}
	if (GameData::inputManager->getKeyHeld(Inputs::LEFT))
	{
		position += Vec2(2.0f, 0.0f);

	}
	if (GameData::inputManager->getKeyHeld(Inputs::RIGHT))
	{
		position += Vec2(-2.0f, 0.0f);

	}
	viewWidth += GameData::inputManager->mouse_scroll;
	viewHeight += GameData::inputManager->mouse_scroll;
	zoom = viewWidth / width;
	if (zoom < 0.0f)
	{
		zoom = 0.01f;
	}
	Vec3 pos3d(position.x, position.y);

	m_projMat = OurMatrix::CreateOrthographic(viewWidth, viewHeight, nearPlane, farPlane);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	m_worldMat = OurMatrix::CreateTrasform(pos3d, rotation, zoom, width, height);
	return false;
}
