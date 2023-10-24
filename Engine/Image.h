#pragma once
#include <string>
#include <vector>
#include "Transform.h"

class Sprite;

namespace Image
{
	void SetTransform(int hImage, Transform transform);
	int Load(std::string filename);
	void Draw(int hImage);
	void Release();
}
