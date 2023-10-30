#pragma once
#include "Engine/GameObject.h"

class SceneTransition
	:public GameObject
{
	bool isCreate_newTable_;

	int table_xsize_;
	int table_zsize_;
public:
	SceneTransition(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

