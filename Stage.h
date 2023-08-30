#pragma once
#include "Engine/GameObject.h"

namespace
{
	const int MODEL_NUM = 5;
	const int XSIZE = 15;
	const int ZSIZE = 15;
	enum MODEL_TYPE
	{
		MODEL_DEFAULT,
		MODEL_BRICK,
		MODEL_GRASS,
		MODEL_SAND,
		MODEL_WATER,
	};
	
}

struct
{
	MODEL_TYPE modelType;
	int height;
}table_[XSIZE][ZSIZE];

class Stage
	:public GameObject
{
	int hModel_[MODEL_NUM];
	

public:
	Stage(GameObject* parent);

	//èâä˙âª
	void Initialize() override;

	//çXêV
	void Update() override;

	//ï`âÊ
	void Draw() override;

	//äJï˙
	void Release() override;
};

