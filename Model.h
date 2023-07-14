#pragma once
#include <string>
#include <vector>
#include "Engine/Transform.h"

class Fbx;

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_;
		Transform transform_;
		std::string fileName_;
	};

	void SetTransform(int hModel, Transform transform);
	int Load(std::string filename);
	void Draw(int hModel);

	//モデルのポインタを入れておくポインタ
	std::vector<ModelData*> modelList;
}
