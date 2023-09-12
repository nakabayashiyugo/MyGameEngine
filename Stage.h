#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>
#include <iostream>

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

class Stage
	:public GameObject
{
	int hModel_[MODEL_NUM];
	
	bool returnButton;
	int mode_;		//0: up   1: down  2: change
	int select_;	//syurui
	int end_;
	
	XMFLOAT3 actPos;

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

	void SetBlock(int x, int z, MODEL_TYPE _type);
	void SetHeight(int x, int z, int _height);



	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

};

