#pragma once
#include <string>
#include <vector>
#include "Engine/Transform.h"

class Fbx;

namespace Model
{
	void SetTransform(int hModel, Transform transform);
	int Load(std::string filename);
	void Draw(int hModel);
}
