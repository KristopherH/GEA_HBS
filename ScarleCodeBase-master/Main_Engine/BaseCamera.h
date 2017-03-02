#pragma once
#include "..\DXTK_Wrapper\CustomMath.h"
#include "..\Main_Engine\GameObjectV2.h"
#include "Enum_container.h"

class PlayerV2;

class BaseCamera : public GameObjectV2
{
public:
	BaseCamera(float _width, float _height, float _nearPlane, float _farPlane, Vec3 _up = Vec3::Up, Vec3 _target = Vec3::Zero);
	~BaseCamera();

	virtual bool Update();

	virtual bool Draw();

	//Getters
	OurMatrix GetProj() { return m_projMat; }
	OurMatrix GetView() { return m_viewMat; }
	OurMatrix GetTransMat() { return m_worldMat; }

	float getPlayerBoxWidth() { return player_box_width; }
	float getPlayerBoxHeight() { return player_box_height; }
	float getPlayerBoxPosX() { return player_box_x; }
	float getPlayerBoxPosY() { return player_box_y; }

	Direction getMovementDirection() override { return movement_direction; }
	void setMovementDirection(Direction _movement_direction) override { movement_direction = _movement_direction; }
	//Setters
	void setPlayerBoxWidth(float _player_box_width) { player_box_width = _player_box_width; }
	void setPlayerBoxHeight(float _player_box_height) { player_box_height = _player_box_height; }
	void setPlayerBoxPosX(float _player_box_x) { player_box_x = _player_box_x; }
	void setPlayerBoxPosY(float _player_box_y) { player_box_y = _player_box_y; }
	void setPlayerTracker(PlayerV2* _player) { player = _player; }

protected:
	//Principle transforms/matrices for this camera
	OurMatrix m_projMat;
	OurMatrix m_viewMat;
	OurMatrix m_worldMat;

	//parameters for setting up a camera
	float width;
	float height;
	float nearPlane;
	float farPlane;

	float player_box_width = 1000.0f;
	float player_box_height = 1000.0f;
	float player_box_x = 0.0f;
	float player_box_y = 0.0f;

	Vec3 m_target;
	Vec3 m_up;

	float rotation = 0.0f;
	float zoom = 1.0f;

	PlayerV2* player = nullptr;
	Direction movement_direction = Direction::NONE;
};
