#pragma once
#include <string>
#include <vector>
#include "Transform.h"
#include "Sprite.h"

namespace Image
{
	void SetTransform(int hImage, Transform transform);
	int Load(std::string filename);
	void Draw(int hImage);
	void Release();
	XMFLOAT3 GetTextureSize(int hImage);
}
