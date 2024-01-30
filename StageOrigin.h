#pragma once
#include "Engine/GameObject.h"
#include "Engine/Direct3D.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <vector>
class SceneTransition;

enum MATHTYPE
{
	MATH_FLOOR,		//��
	MATH_WALL,		//��
	MATH_HOLE,		//��
	MATH_CONVEYOR,	//�R���x�A
	MATH_TOGETOGE,	//�Ƃ��Ƃ��̂��
	MATH_PITFALL,	//���Ƃ���
	MATH_START,		//�X�^�[�g�}�X
	MATH_GOAL,		//�S�[���}�X
	MATH_MAX,
};

struct MATHDEDAIL
{
	MATHTYPE mathType_;
	Transform mathPos_;
};

struct TOGETOGEROUTE
{
	Transform route_;
	XMFLOAT3 initPos_;
};

class StageOrigin
{
protected:
	const int MATHSIZE = 30;

	std::vector<std::vector<MATHDEDAIL>> math_;
	std::vector<TOGETOGEROUTE> tTgtgRoute_;

	SceneTransition* pTrans_;

	int XSIZE;
	int ZSIZE;

public:
	void Math_Resize(int _xsize, int _zsize, std::vector<std::vector<MATHDEDAIL>> *_math)
	{
		_math->resize(_xsize);
		for (int x = 0; x < _xsize; x++)
		{
			_math->at(x).resize(_zsize);
		}
	}
	void Math_Resize(int _xsize, int _zsize, std::vector<std::vector<bool>>* _math)
	{
		_math->resize(_xsize);
		for (int x = 0; x < _xsize; x++)
		{
			_math->at(x).resize(_zsize);
			for (int z = 0; z < _zsize; z++)
			{
				_math->at(x).at(z) = false;
			}
		}
	}
};

