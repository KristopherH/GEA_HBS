#pragma once
#include "EditableGameObject.h"
#include "RopeNode.h"

class Rope : public EditableGameObject
{
public:
	Rope(Vec2 pos, 
		Texture * _texture,
		int numOfNodes,
		float springConst,
		float springLength,
		float springFrictionConst,
		Vec2 ropeSize,
		vector<GameObject*>* go_list);
	~Rope() override;

	bool Update(float dt) override;
	bool Draw() override;

	void updateParenting();

	void playerGrabbed(RopeNode* nodeGrabbed, Vec2 playerPosRelativeToNode);

	virtual void toggleEditing() override;

	void redoNodes();

	void addNode();
	void removeNode();

	int getLength();

	Vec2 getSize() override;
	Vec2 getPosition() override;
	Vec2 getScale() override;
	Vec2 getOrigin() override;
	float getRotation() override;

	void setSize(Vec2* _size) override;
	void setScale(Vec2* _scale)override;
	void setOrigin(Vec2* _origin) override;
	void setPosition(Vec2* _pos) override;
	void movePosition(Vec2* _translation) override;

private:
	int numOfNodes;

	bool grabbedPlayer = false;
	RopeNode* playerNode = 0;
	Vec2 playerPos;
	float springConst;
	float springLength;
	float springFrictionConst;
	std::vector<RopeNode*> ropeNodes;
	Vec2 ropeSize;
};
