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
		MATH_FLOOR,		//��
		MATH_WALL,		//��
		MATH_HOLL,		//��
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
		int converyor_rotate_;
	};

	std::vector<std::vector<MATHDEDAIL>> math_;

	SceneTransition* pTrans_;

	int XSIZE;
	int ZSIZE;
};

