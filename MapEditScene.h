#pragma once
#include "StageOrigin.h"

const int MATH_CHANGE_NUM_LIMIT = 5;

class MapEditScene
	:public GameObject, StageOrigin
{
	int hPict_[MATH_MAX + 1];
	int YSIZE;
	int mathtype_;
	int save_Num_;
	int mathChangeNum_;

	XMFLOAT3 texture_size_;

	std::vector<std::vector<MATHDEDAIL>> math_origin_;
public:
	MapEditScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	void Write();
	void Read();

	void SetMathChangeNum();
};

