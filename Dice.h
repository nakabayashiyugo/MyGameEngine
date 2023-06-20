#pragma once
#include "Quad.h"

class Dice
	:public Quad
{
public:
	virtual void InitVertexData() override;

	virtual void InitIndexData()override;
};

