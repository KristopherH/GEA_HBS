#pragma once
#include "EditableGameObject.h"
#include "ballistics.h"
#include <map>
#include <string>

class Gun : public EditableGameObject
{
	friend class LevelLoader;
public:

	Gun();
	~Gun();

	bool Update(float dt) override;
	bool Draw() override;

	virtual void toggleEditing() override;

	void nextBulletDirection();
	void prevBulletDirection();

	void setBulletSpeed(float wantedSpeed) { bulletSpeed = wantedSpeed; }
	void setShootTime(float _timer) { ShootTime = _timer; };
	void setBD(BulletDirecton _BD) { wanted_BD = _BD; };

private:

	float timer = 10;
	float ShootTime = 3;
	float bulletSpeed = 0.0002;
	BulletDirecton wanted_BD = BD_Target;
	std::map<BulletDirecton, std::string> directionNames;
};