#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Camera.h"
#include "Texture.h"
#include "Quad.h"

class Dice
	:public Quad
{
public:
	virtual HRESULT Initialize() override;
};

