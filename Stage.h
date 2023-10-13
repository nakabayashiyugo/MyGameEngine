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

class Stage
	:public GameObject
{
	int hModel_[MODEL_NUM];
	
	bool isRetturn_;
	int mode_;		//0: up   1: down  2: change
	int select_;	//syurui
	//table_History�̈�ԍŌ�̗v�f
	int retTgt_;

	std::string savefile_;  //�ǂݍ��ރt�@�C���̎w��
	
	XMFLOAT3 actPos;

	struct tableStruct
	{
		MODEL_TYPE modelType;
		int height;
		float rayDist;
		bool IsColRay;
	};

	tableStruct table_[XSIZE][ZSIZE];

	std::vector<tableStruct[XSIZE][ZSIZE]> table_History_;

public:
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetBlock(int x, int z, MODEL_TYPE _type);
	void SetHeight(int x, int z, int _height);

	void TransTableHis(int _x, int _z, tableStruct* tabHis);

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	void CreateNewTable();

	void Write();
	void Read();
	void SaveAs();

};

