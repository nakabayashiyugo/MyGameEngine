#pragma once
#include "Engine/GameObject.h"
#include "Engine/Direct3D.h"
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

	std::vector<std::vector<MATHDEDAIL>> math_;

	SceneTransition* pTrans_;

	int XSIZE;
	int ZSIZE;

public:
	void Math_Resize(int _xsize, int _zsize)
	{
		math_.resize(_xsize);
		for (int x = 0; x < _xsize; x++)
		{
			math_.at(x).resize(_zsize);
			for (int y = 0; y < _zsize; y++)
			{

			}
		}
	}
};

