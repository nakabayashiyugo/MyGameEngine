#pragma once
#include <string>
#include <vector>
#include "Transform.h"
#include "Fbx.h"

namespace Model
{
	void SetTransform(int hModel, Transform transform);
	int Load(std::string filename);
	void Draw(int hModel);
	void Release();

	void RayCast(int hModel, RayCastData& rayData);
}
