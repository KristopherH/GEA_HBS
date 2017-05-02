#pragma once
#include <string>
#include <map>
#include "EditableGameObject.h"

enum PLATFORM_TYPE
{
	FIRST,
	STANDARD,
	SLOW,
	STICKY,
	SPEED,
	CONVEYOR_LEFT,
	CONVEYOR_RIGHT,
	JUMP,
	END
};

class Platform : public EditableGameObject
{
public:
	~Platform() = default;

	void changeType(PLATFORM_TYPE);
	PLATFORM_TYPE getPlatformType() { return platform_type; }

	static Platform* create(PLATFORM_TYPE);
	static void init();

	virtual void toggleEditing() override;

	void nextType();
	void prevType();

protected: 
	// functions
	Platform(Sprite* sprite, std::string _name, std::string _tag);

	void conveyorPlatform(bool leftOrRight);
	static std::map<std::string, Texture*> platform_sprites;

	// vars
	PLATFORM_TYPE platform_type;
	
};
