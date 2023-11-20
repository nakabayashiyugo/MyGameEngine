#pragma once
#include "StageOrigin.h"

class MapEditScene
	:public GameObject, StageOrigin
{
	int hPict_[MATH_MAX + 1];

	int YSIZE;

	int mathtype_;
public:
	MapEditScene(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	void Write();
	void Read();
};

