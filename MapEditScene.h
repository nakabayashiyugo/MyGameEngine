#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <vector>
class SceneTransition;

const int MATHSIZE = 30;

enum MATHTYPE
{
	MATH_FLOOR,		//床
	MATH_WALL,		//壁
	MATH_HOLL,		//穴
	MATH_CONVEYOR,	//コンベア
	MATH_TOGETOGE,	//とげとげのやつ
	MATH_PITFALL,	//落とし穴
	MATH_START,		//スタートマス
	MATH_GOAL,		//ゴールマス
	MATH_MAX,
};

struct MATHDEDAIL
{
	MATHTYPE mathType_;
	Transform mathPos_;
	int converyor_rotate_;
};

class MapEditScene
	:public GameObject
{
	int XSIZE = 10;
	int YSIZE = 10;

	SceneTransition* pTrans_;

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

