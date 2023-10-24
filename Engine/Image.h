#pragma once
#include <string>
#include <vector>
#include "Transform.h"

class Sprite;

namespace Image
{
	void SetTransform(int hImage, Transform transform);
	void SetRect(int hImage, int x, int y, int width, int height);
	int Load(std::string filename);
	void Draw(int hImage);
	void Release();
}
