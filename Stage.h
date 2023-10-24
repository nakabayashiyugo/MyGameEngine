#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>

namespace
{
	const int MODEL_NUM = 5;
	const int XSIZE = 15;
	const int ZSIZE = 15;
	const int RET_CNT_LIMIT = 20;
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

struct vec
{
	int x;
	int z;
};

class Stage
	:public GameObject
{
	int hModel_[MODEL_NUM];
	
	bool isRedo_, isUndo_;
	int curHistory_Target_;
	int mode_;		//0: up   1: down  2: change
	int select_;	//syurui

	std::string savefile_;  //読み込むファイルの指定
	
	XMFLOAT3 actPos;

	struct tableStruct
	{
		MODEL_TYPE modelType;
		int height;
		float rayDist;
		bool isRayHit;
	};

	struct tableHistory
	{
		MODEL_TYPE modelType;
		int height;
		vec pos;
	};

	std::vector<std::vector<tableStruct>> table_;

	std::vector<tableHistory> table_History;

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
	BOOL CreateTableDialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	void TableChange();

	void DeleteTableHistory();

	void CreateNewTable();

	void Write();
	void Read();
	void SaveAs();

};

