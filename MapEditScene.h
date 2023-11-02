#pragma once
#include "StageOrigin.h"

class MapEditScene
	:public GameObject, StageOrigin
{
	int XSIZE;
	int YSIZE;

	int hPict_[MATH_MAX + 1];
	std::vector<std::vector<MATHDEDAIL>> math_;

	int mathtype_;
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
};

