#pragma once
#include "Engine/GameObject.h"

class Stage
	:public GameObject
{
	int hModel_;
public:
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

