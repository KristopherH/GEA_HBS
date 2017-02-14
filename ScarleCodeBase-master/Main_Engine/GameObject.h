#pragma once

struct Vec2 { float x; float y; }; //DELETE THIS LINE WHEN THE CUSTOMMATH.H IS DONE

class GameObject
{
public:
	GameObject();
	~GameObject();
	
	bool init();
	bool update();

	Vec2 getPosition();
	Vec2 getSize();
	float getOpacity();

	void setPosition(Vec2 _position);
	void setSize(Vec2 _size);
	void setOpacity(float _opacity);

private:
	Vec2 position;
	Vec2 size;
	float opacity = 0.0f;

};