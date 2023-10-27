#pragma once
#include "Engine/GameObject.h"
class Sprite;

const int XSIZE = 15;
const int YSIZE = 15;
const int MATHSIZE = 30;

enum MATHTYPE
{
	MATH_FLOOR,		//��
	MATH_WALL,		//��
	MATH_HOLL,		//��
	MATH_CONVEYOR,	//�R���x�A
	MATH_TOGETOGE,	//�Ƃ��Ƃ��̂��
	MATH_PITFALL,	//���Ƃ���
	MATH_MAX,
};

struct MATHDEDAIL
{
	MATHTYPE mathType_;
	Transform mathPos_;
};

class SpriteTest
	:public GameObject
{
	int hPict_[MATH_MAX];
	MATHDEDAIL math_[XSIZE][YSIZE];
public:
	SpriteTest(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

