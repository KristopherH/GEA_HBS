#pragma once
#include "GameData.h"
#include "BaseCamera.h"
#include "Input_Manager.h"

class LevelEditorCamera : public BaseCamera
{
public:
	LevelEditorCamera(float _width, float _height, float _nearPlane, float _farPlane, Vec3 _up = Vec3::Up, Vec3 _target = Vec3::Zero);
	~LevelEditorCamera();

	virtual bool Update(float dt) override;

private:
	bool editCam = true;
	float viewWidth = 0;
	float viewHeight = 0;
};