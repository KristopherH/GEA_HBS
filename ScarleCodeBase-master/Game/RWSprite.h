#pragma once
#include "VBGO.h"
#include "vertex.h"

class RWSprite : public VBGO
{
public:
	RWSprite()
	{};
	virtual ~RWSprite()
	{};

	//initialise the Veretx and Index buffers for the cube
	void init(int _size, ID3D11Device* _GD);

protected:
	//this is to allow custom versions of this which create the basic cube and then distort it
	//see VBSpiral, VBSpiked and VBPillow
	virtual void Transform()
	{};

	int m_size;
	myVertex* m_vertices;
};