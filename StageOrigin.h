#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <vector>
class SceneTransition;


class StageOrigin
{
protected:

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

	SceneTransition* pTrans_;

	int XSIZE;
	int YSIZE;
};

