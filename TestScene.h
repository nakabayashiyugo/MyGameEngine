#pragma once
#include "Engine/GameObject.h"

class TestScene
	:public GameObject
{
public:
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

