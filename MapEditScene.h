#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>
class Sprite;

const int XSIZE = 15;
const int YSIZE = 15;
const int MATHSIZE = 30;

enum MATHTYPE
{
	MATH_FLOOR,		//床
	MATH_WALL,		//壁
	MATH_HOLL,		//穴
	MATH_CONVEYOR,	//コンベア
	MATH_TOGETOGE,	//とげとげのやつ
	MATH_PITFALL,	//落とし穴
	MATH_MAX,
};

struct MATHDEDAIL
{
	MATHTYPE mathType_;
	Transform mathPos_;
};

class MapEditScene
	:public GameObject
{
	int hPict_[MATH_MAX];
	MATHDEDAIL math_[XSIZE][YSIZE];

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
};

