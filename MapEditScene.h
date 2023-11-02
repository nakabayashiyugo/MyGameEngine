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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	void Write();
};

