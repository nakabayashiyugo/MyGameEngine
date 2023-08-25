#pragma once
#include "Engine/GameObject.h"

class Controller
	:public GameObject
{
	XMVECTOR velocity_;
public:
	Controller(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

