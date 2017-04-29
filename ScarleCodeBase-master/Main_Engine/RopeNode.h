#pragma once
//C++
#include <string>

//OURS
#include "GameObject.h"
#include "Sprite.h"
class Rope;

class RopeNode : public GameObject
{
public:
	RopeNode(Sprite* sprite, std::string _name, std::string _tag);
	RopeNode(Sprite* _sprite, 
		float springConst,
		float springLength,
		float springFrictionConst);

	bool Update(float dt) override;
	void gravityUpdate() override;
	bool Draw() override;

	void setPrevNode(RopeNode* rope) { prevNode = rope; first = false; }
	void setNextNode(RopeNode* rope) { nextNode = rope; }
	void setParent(Rope* rope) { parent = rope; }

	Rope* parent;

private:
	bool first = true;

	RopeNode* prevNode;
	RopeNode* nextNode;
	float length;

	float springConst;
	float springLength;
	float springFrictionConst;
};

