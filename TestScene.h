#pragma once
#include "Engine/GameObject.h"

class TestScene
	:public GameObject
{
	bool isCreate_newTable_;

	int table_xsize_;
	int table_zsize_;
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

	void SetCreateNewTable(bool _isCreate);

	void SetTableSize(int _xsize, int _zsize);

	int GetTableXSIZE();
	int GetTableZSIZE();
};

