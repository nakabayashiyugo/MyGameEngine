#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>

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
		MODEL_MAX,
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
	
	int mode_;		//0: up   1: down  2: change
	int select_;	//syurui

public:
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetBlock(int x, int z, MODEL_TYPE _type);
	void SetHeight(int x, int z, int _height);

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

};

